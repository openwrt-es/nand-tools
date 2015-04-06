/*
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 * Copyright (C) 2015 Álvaro Fernández Rojas <noltari@gmail.com>
 */
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "nand.h"

int main(int argc, char **argv) {
	struct stat st;
	char *ifile, *ofile;
	int c, ifd, ofd, nand_entries, version;
	int nand_page = NAND_PAGE_DEF;
	int nand_oob = NAND_OOB_DEF;
	int check_entries = NAND_CHECK_ENTRIES;
	int debug = DEBUG_DEF;

	while ((c = getopt(argc, argv, "b:dfi:o:p:v")) != -1) {
		switch (c) {
			case 'b':
				nand_oob = atoi(optarg);
				break;
			case 'd':
				debug = 1;
				break;
			case 'f':
				check_entries = 0;
				break;
			case 'i':
				ifile = optarg;
				break;
			case 'o':
				ofile = optarg;
				break;
			case 'p':
				nand_page = atoi(optarg);
				break;
			case 'v':
				version = 1;
				break;
			case '?':
				if (optopt == 'i' || optopt == 'o') {
					pr_err("Option -%c requires an argument\n", optopt);
				}
				else if (isprint(optopt)) {
					pr_err("Unkown option \"-%c\"\n", optopt);
				}
				else {
					pr_err("Unkown option character \"%x\"\n", optopt);
				}

				return -ERROR_ARGS;
		}
	}

	if (version) {
		nand_tools_version();

		if(!ifile || !ofile) {
			return 0;
		}
	}

	if (!ifile || !ofile) {
		pr_err("Input and output files must be specified\n");
		return -ERROR_ARGS;
	}

	ifd = open(ifile, O_RDONLY);
	if (!ifd) {
		pr_err("Input file error\n");
		return -ERROR_FILE;
	}

	ofd = open(ofile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU + S_IRWXG + S_IRWXO);
	if (!ofd) {
		pr_err("Output file error\n");
		return -ERROR_FILE;
	}

	fstat(ifd, &st);
	nand_entries = st.st_size / (nand_page + nand_oob);
	if (st.st_size % (nand_page + nand_oob) != 0 && check_entries) {
		pr_err("Invalid NAND entries\n");
		return -ERROR_ENTRIES;
	}

	return nand_clean_oob(debug, ifd, ofd, st.st_size, nand_page, nand_oob, nand_entries);
}
