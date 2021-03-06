#ifndef NB_DB_H_INCLUDED
#define NB_DB_H_INCLUDED

/*
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

struct nb_db;
struct nb_key;

typedef int (*nb_db_reqf_t)(struct nb_db *db, struct nb_key *key);

struct nb_db_if {
	const char *name;
	int (*init)(struct nb_db *db, size_t value_size);
	void (*free)(struct nb_db *db);
	int (*connect)(struct nb_db *db, struct nb_options *opts);
	void (*close)(struct nb_db *db);
	int (*recv)(struct nb_db *db, int count, int *missed);
	nb_db_reqf_t insert;
	nb_db_reqf_t replace;
	nb_db_reqf_t update;
	nb_db_reqf_t del;
	nb_db_reqf_t select;
};

struct nb_db {
	struct nb_db_if *dif;
	void *priv;
};

extern struct nb_db_if *nb_dbs[];

struct nb_db_if *nb_db_match(const char *name);

#endif
