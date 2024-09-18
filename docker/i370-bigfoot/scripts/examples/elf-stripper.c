/*
 * Strip out ELF headers from i370 ELF files, so that they can be IPL'ed.
 *
 * Minimal, bare-bones implementation. The ELF headers are read in,
 * and the ELF text sections are copied to stdout. That's it. The
 * result should be a bootable image, assuming the PSW occurs in the
 * first location.
 *
 * This is meant to be a simple demo showing the principles of
 * operation, and not a fancy tool.
 *
 * Linas Vepstas September 2024
 */

#include <arpa/inet.h>
#include <elf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <i370 ELF executable>\n", argv[0]);
		exit (1);
	}

	/* Open the ELF file	*/
	const char *elfname = argv[1];
	FILE *fp = fopen(elfname, "r");
	if (NULL == fp)
	{
		fprintf(stderr, "Error: Can't find ELF binary %s\n", elfname);
		exit (1);
	}
	fprintf(stderr, "Info: processing '%s'\n", elfname);

	/* Read the ELF header */
	Elf32_Ehdr* ehdr = (Elf32_Ehdr*) malloc(sizeof(Elf32_Ehdr));
	size_t nr = fread(ehdr, 1, sizeof(Elf32_Ehdr), fp);
	if (sizeof(Elf32_Ehdr) != nr)
	{
		fprintf(stderr,
			"Error: ELF file is too short, got %d bytes, expecting %ld\n",
			nr, sizeof(Elf32_Ehdr));
		exit (1);
	}

	/* Minimal verification */
	if (ntohs(ehdr->e_type) != ET_EXEC)
	{
		fprintf(stderr,
			"Error: Expecting executable ELF file got %d\n",
			ntohs(ehdr->e_type));
		exit (1);
	}

	fprintf(stderr,
		"Info: Found ELF machine=%d version=%d\n",
		ntohs(ehdr->e_machine), ntohl(ehdr->e_version));

	if (EM_S370 != ntohs(ehdr->e_machine))
	fprintf(stderr,
		"Warn: Expecting EM_S370 for the machine, got something else\n");

	/* ------------------------------------------ */
	/* Report on the segments */

	fprintf(stderr,
		"Info: Found ELF entry point at 0x%x, pheader at 0x%x, expect %d segments\n",
		ntohl(ehdr->e_entry), ntohl(ehdr->e_phoff), ntohs(ehdr->e_phnum));

	const size_t npbytes = ntohs(ehdr->e_phentsize) * ntohs(ehdr->e_phnum);
	Elf32_Phdr* phdr = malloc(npbytes);
	if (NULL == phdr)
	{
		fprintf(stderr, "Error: Corrupt elf header\n");
		exit (1);
	}

	/* Seek to program header */
	int rc = fseek(fp, ntohl(ehdr->e_phoff), SEEK_SET);
	if (0 != rc)
	{
		int norr = errno;
		fprintf(stderr, "Error: Unable to find program header: %d %s\n",
			norr, strerror(norr));
		exit(1);
	}

	/* Read the program headers */
	nr = fread(phdr, 1, npbytes, fp);
	if (npbytes != nr)
	{
		fprintf(stderr,
			"Error: Expecting %d bytes git %ld bytes for '%s' program header\n",
			npbytes, nr, elfname);
		exit (1);
	}

	/* Print everything. */
	for (int i=0; i<ntohs(ehdr->e_phnum); i++)
	{
		fprintf(stderr,
			"Segment %d type=%d off=0x%x vaddr=0x%x paddr=0x%x sz=%ld memsz=%ld flags=0x%x\n",
			i, ntohl(phdr[i].p_type), ntohl(phdr[i].p_offset),
			ntohl(phdr[i].p_vaddr), ntohl(phdr[i].p_paddr),
			ntohl(phdr[i].p_filesz), ntohl(phdr[i].p_memsz),
			ntohl(phdr[i].p_flags));

		/* Very old elf-i370 binaries did not have an appropriate
		 * segment types.  Thus, we accept PT_NULL, here. */
		if ((ntohl(phdr[i].p_type) == PT_LOAD) &&
		    (ntohl(phdr[i].p_type) == PT_NULL)) continue;

		/* Compute the offset in the file, and seek to it. */
		/* XXX This is incorrect, unless the linker spec sets
		 * up the text segment at address zero. This is doable,
		 * but a pain in the neck, so we don't do this. See
		 * note above. */
		long off = ntohl(phdr[i].p_offset);
		int rc = fseek(fp, off, SEEK_SET);
		if (0 != rc)
		{
			int norr = errno;
			fprintf(stderr, "Error: Can't seek; errno=%d %s\n",
				norr, strerror(norr));
			exit(1);
		}

		/* Read p_filesz bytes. */
		size_t fsz = ntohl(phdr[i].p_filesz);
		char *code = malloc(fsz);
		nr = fread(code, 1, fsz, fp);
		if (fsz != nr)
		{
			fprintf(stderr,
				"Error: short read, got %d bytes, expecting %ld\n", nr, fsz);
			exit (1);
		}

		/* Write p_filesz bytes. */
		fwrite(code, 1, fsz, stdout);

		/* Pad out the rest */
		for (int n=fsz; n<ntohl(phdr[i].p_memsz); n++)
			fputc(0, stdout);

		free(code);
	}

	return 0;
}
