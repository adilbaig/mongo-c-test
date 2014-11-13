/*
 * quotes.c
 *
 *  Created on: 13-Nov-2014
 *      Author: adil
 */

#include "/usr/include/libbson-1.0/bson.h"
#include "/usr/include/libmongoc-1.0/mongoc.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	mongoc_client_t *client;
	mongoc_collection_t *collection;
	mongoc_cursor_t *cursor;
	const bson_t *doc;
	bson_t *query;
	char *str;

	mongoc_init();

	client = mongoc_client_new("mongodb://localhost:27017/");
	collection = mongoc_client_get_collection(client, "stockopedia",
			"instruments");

	query = bson_new();
	bson_t *fields = bson_new();
	BSON_APPEND_INT32(fields, "RIC", 1);

	cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 0, 0,
			query, fields, NULL);

	bson_iter_t iter;
	const bson_value_t *value;

	while (mongoc_cursor_next(cursor, &doc)) {
		str = bson_as_json(doc, NULL);
		printf("%s\n", str);

		if (bson_iter_init(&iter, doc)) {
			while (bson_iter_next(&iter)) {
				printf("Found a field named: %s\n", bson_iter_key(&iter));

				value = bson_iter_value(&iter);
				if (value->value_type == BSON_TYPE_UTF8) {
					printf("It's a UTF8 : '%s'\n", value->value.v_utf8.str);
				}
			}
		}

		//printf("Found element key : '%s'\n", bson_iter_key(&iter));

//		if (bson_iter_init(&iter, doc)) {
//
//		}

		bson_free(str);
	}

	//Now fetch quotes for each RIC

	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	mongoc_collection_destroy(collection);
	mongoc_client_destroy(client);

	return 0;
}
