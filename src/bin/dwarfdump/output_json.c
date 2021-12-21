/*
 SPDX-License-Identifier: MIT
 
 Copyright (c) 2021-2023 Shigehiro Fukase

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <stdio.h>
#include "libdwarf.h"
#include "dd_globals.h"
#include "parson.h"
#include "output_json.h"

static FILE *json_wfp = NULL;
void json_init(void **prv, const char * name) {
    if (!glflags.json_root_value) {
        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);

        if (name) {
            json_object_set_string(root_object, JSON_NODE_FILENAME, name);
        }
        json_object_set_empty_array(root_object, JSON_NODE_SECTION);
        glflags.json_root_value = root_value;
    }
    if (prv) {
        *prv = glflags.json_root_value;
    }
    if (glflags.json_file) {
        json_wfp = fopen(glflags.json_file, "w");
        if (!json_wfp) {
            fprintf(stderr, "%s ERROR:  "
                "can't open save file.... %s\n",
                glflags.program_name,
                glflags.json_file);
        }
    }
}
void json_term(void *rv) {
    if (rv && (rv != glflags.json_root_value)) {
        json_value_free(rv);
    }
    json_value_free(glflags.json_root_value);
    glflags.json_root_value = NULL;

    if (json_wfp) {
        fclose(json_wfp);
    }
}
/* get 'DW_TAG_compie_unit:DW_AT_name' and 'DW_TAG_compie_unit:DW_AT_comp_dir' */
static int get_comp_info(JSON_Value *json_sec_val, const char ** cunitp, const char ** cdirp) {
    JSON_Object *json_sec_obj;
    JSON_Array *json_sec_die;
    JSON_Object *die0;
    JSON_Array *json_sec_attr;
    size_t attrs;
    size_t i;
    const char * cunit = NULL;
    const char * cdir = NULL;
    int ret = -1;

    if ((json_sec_obj = json_value_get_object(json_sec_val)) == NULL) return -1;
    if ((json_sec_die = json_object_dotget_array(json_sec_obj, JSON_NODE_DIE)) == NULL) return -1;
    if ((die0 = json_array_get_object(json_sec_die, 0)) == NULL) return -1;
    if ((json_sec_attr = json_object_dotget_array(die0, JSON_NODE_DIE_ATTR)) == NULL) return -1;
    attrs = json_array_get_count(json_sec_attr);
    for (i=0; i<attrs; i++) {
        JSON_Object * attr = json_array_get_object(json_sec_attr, i);
        if (attr) {
            const char * name = json_object_get_string(attr, JSON_NODE_DIE_ATTR_NAME);
            const char * path = json_object_get_string(attr, JSON_NODE_DIE_ATTR_VALUE);
            if (strcmp(name, "DW_AT_name") == 0) {
                cunit = path;
                ret = 0;
            } else if (strcmp(name, "DW_AT_comp_dir") == 0) {
                cdir = path;
                ret = 0;
            }
        }
    }
    if (cunitp) *cunitp = cunit;
    if (cdirp) *cdirp = cdir;
    return ret;
}
static const char* basename(const char* path) {
    const char * p = path + strlen(path);
    for (; p>path; p--) {
        if ((*p == '/') || (*p == '\\')) {
            return p+1;
        }
    }
    return path;
}
static int chkopt_compile_unit(const char * cunit) {
    if (cunit && (glflags.json_restrict_unit_num > 0)) {
		const char * cunitbase = basename(cunit);
        int i;
		for (i=0; i<glflags.json_restrict_unit_num; i++) {
            const char* rname = glflags.json_restrict_unit_list[i];
            const char * rnamebase = basename(rname);
            if (strcmp(cunitbase, rnamebase) == 0) {
                return 0;
            }
        }
        return -1;
    }
    return 0;
}
static int chkopt_section(JSON_Value *json_sec_val) {
    const char * cunit = NULL;
    const char * cdir = NULL;
    int chkunit;
    if (get_comp_info(json_sec_val, &cunit, &cdir) < 0) return 0;
    chkunit = chkopt_compile_unit(cunit);
    return chkunit;
}
void json_add_section(JSON_Value *json_sec_val) {
    if (chkopt_section(json_sec_val) == 0) {
        JSON_Value *root_value = glflags.json_root_value;
        JSON_Object *root_object = json_value_get_object(root_value);
        JSON_Array *arr = json_object_get_array(root_object, JSON_NODE_SECTION);
        json_array_append_value(arr, json_sec_val);
    }
}
JSON_Status json_object_set_empty_array(JSON_Object *object, const char *name) {
    JSON_Value *val = json_value_init_array();
    JSON_Array *arr = json_value_get_array(val);
    json_array_clear(arr);
    return json_object_set_value(object, name, val);
}
char * json_get_string(void *rv) {
    JSON_Value *root_value;
    JSON_Object *root_object;
    char *serialized_string = NULL;

    if (!rv) {
        rv = glflags.json_root_value;
    }
    root_value = (JSON_Value *)rv;
    root_object = json_value_get_object(root_value);
    serialized_string = json_serialize_to_string_pretty(root_value);
    return serialized_string;
}
void json_dump(void *rv) {
    char *serialized_string = json_get_string(rv);
    // puts(serialized_string);
    if (json_wfp) {
        fputs(serialized_string, json_wfp);
    }
    json_free_serialized_string(serialized_string);
}
void json_save(const char * path, void *rv) {
    if (path) {
        FILE *fp = fopen(path, "w");
        if (fp) {
            char *serialized_string = json_get_string(rv);
            fprintf(fp, "%s\n", serialized_string);
            fclose(fp);
            json_free_serialized_string(serialized_string);
        } else {
            fprintf(stderr, "%s ERROR:  "
                "can't open save file.... %s\n",
                glflags.program_name,
                path);
        }
    }
}
