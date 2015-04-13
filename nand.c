/*
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 * Copyright (C) 2015 Álvaro Fernández Rojas <noltari@gmail.com>
 */
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "nand.h"
#include "version.h"

/**
 * Prints nandtools version
 */
void nand_tools_version(void) {
	printf("%s %s\n", VER_NAME, VER_CODE);
}

/**
 * Removes OOB entries from NAND backup in order to create a flashable backup
 */
int nand_clean_oob(int debug, int ifd, int ofd, ssize_t size, int nand_page, int nand_oob, int nand_entries) {
	int i, ibuf_size, obuf_size;
	uint8_t *ibuf, *obuf;

	ibuf_size = size;
	obuf_size = size - nand_entries * nand_oob;

	ibuf = malloc(ibuf_size);
	if (!ibuf) {
		pr_err("Error allocating input buffer\n");
		return -ERROR_PTR;
	}

	obuf = malloc(obuf_size);
	if (!obuf) {
		free(ibuf);
		pr_err("Error allocating output buffer\n");
		return -ERROR_PTR;
	}

	if (lseek(ifd, 0, SEEK_SET) < 0) {
		free(ibuf);
		free(obuf);
		pr_err("Error seeking input file\n");
		return -ERROR_SEEK;
	}

	if (debug) {
		pr_info("Reading input file\n");
	}
	if (read(ifd, ibuf, ibuf_size) < 0) {
		free(ibuf);
		free(obuf);
		pr_err("Error reading input file\n");
		return -ERROR_READ;
	}

	if (debug) {
		pr_info("Copying NAND pages\n");
	}
	for(i = 0; i < nand_entries; i++) {
		memcpy(obuf + i * nand_page, ibuf + i * (nand_page + nand_oob), nand_page);
	}

	if (debug) {
		pr_info("Writing output file\n");
	}
	if (write(ofd, obuf, obuf_size) < 0) {
		free(ibuf);
		free(obuf);
		pr_err("Error writing output file\n");
		return -ERROR_READ;
	}

	pr_info("OOB removed from NAND backup\n");

	free(ibuf);
	free(obuf);

	return 0;
}
