/*
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 * Copyright (C) 2015 Álvaro Fernández Rojas <noltari@gmail.com>
 */
#ifndef _NAND_H
#define _NAND_H

#define NAND_PAGE_DEF 2048
#define NAND_OOB_DEF 64
#define NAND_CHECK_ENTRIES 1
#define DEBUG_DEF 0
#define DEBUG_PROG 5

#define pr_info(...) printf(__VA_ARGS__)
#define pr_err(...) fprintf(stderr, __VA_ARGS__)

enum errors {
	NO_ERROR = 0,
	ERROR_ARGS,
	ERROR_PTR,
	ERROR_FILE,
	ERROR_SEEK,
	ERROR_READ,
	ERROR_WRITE,
	ERROR_ENTRIES
};

int nand_clean_oob(int debug, int ifd, int ofd, ssize_t size, int nand_page, int nand_oob, int nand_entries);
void nand_tools_version(void);

#endif /* _NAND_H */
