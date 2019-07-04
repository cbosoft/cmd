#include <stdlib.h>
#include <stdio.h>
#include <cvec.h>

#include "cmd.h"
#include "cJSON.h"

#define CHECKJSON(J,S) if (J == NULL) ferr("load", "parameter \"%s\" missing from json", S)

void save(Sim *s, const char* path) 
{

  cJSON *json = cJSON_CreateObject();

  if (json == NULL)
    ferr("save", "error creating JSON object");

  // TODO add run params to json
  cJSON *json_box = cJSON_CreateDoubleArray(s->box, NDIM);
  cJSON_AddItemToObject(json, "box", json_box);

  cJSON *json_particle_list = cJSON_CreateArray();
  for (cvec_uint i = 0; i < s->number_particles; i++) {
    Particle *p = s->particles[i];
    cJSON *json_particle = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_particle, "id", p->id);
    cJSON_AddNumberToObject(json_particle, "diameter", p->diameter);
    cJSON_AddNumberToObject(json_particle, "mass", p->mass);

    cJSON *json_position = cJSON_CreateDoubleArray(p->position, NDIM);
    cJSON_AddItemToObject(json_particle, "position", json_position);

    cJSON *json_force = cJSON_CreateDoubleArray(p->force, NDIM);
    cJSON_AddItemToObject(json_particle, "force", json_force);

    cJSON_AddItemToArray(json_particle_list, json_particle);

  }

  cJSON_AddItemToObject(json, "particles", json_particle_list);

  char *json_string = cJSON_Print(json);

  FILE *fp = fopen(path, "w");

  cJSON_Delete(json);

  if (fp == NULL)
    ferr("save", "could not open file \"%s\"", path);

  fprintf(fp, "%s", json_string);
  fclose(fp);

}




Sim *load(const char *path)
{
  Sim *s = alloc_sim();

  char *json_str;

  FILE *fp = fopen(path, "r");

  if (fp == NULL)
    ferr("load", "could not open file \"%s\"", path);

  cvec_uint filelength = 0;
  char ch;
  while ((ch = fgetc(fp)) != EOF) filelength++;

  json_str = calloc(filelength+1, sizeof(char));

  fseek(fp, 0, SEEK_SET);
  fread(json_str, filelength, sizeof(char), fp);
  
  fclose(fp);

  cJSON *json = cJSON_Parse(json_str);
  
  cJSON *json_box = cJSON_GetObjectItem(json, "box");
  cJSON *json_particle_list = cJSON_GetObjectItem(json, "particles");

  cvec_uint i;

  i = 0;
  cJSON *element;
  cJSON_ArrayForEach(element, json_box) {
    s->box[i] = element->valuedouble;
    i++;
  }
  
  i = 0;
  cJSON *json_particle;
  cJSON_ArrayForEach(json_particle, json_particle_list) {
    Particle *p = alloc_particle();
    
    // get position {{{
    
    cJSON *json_position = cJSON_GetObjectItem(json_particle, "position");
    CHECKJSON(json_position, "position");
    
    i = 0;
    cJSON_ArrayForEach(element, json_position) {
      p->position[i] = element->valuedouble;
      i++;
    }

    // }}}
    // get force {{{

    cJSON *json_force = cJSON_GetObjectItem(json_particle, "force");
    CHECKJSON(json_force, "force");
    
    i = 0;
    cJSON_ArrayForEach(element, json_force) {
      p->force[i] = element->valuedouble;
      i++;
    }

    // }}}
    // get diameter {{{

    cJSON *json_diameter = cJSON_GetObjectItem(json_particle, "diameter");
    CHECKJSON(json_diameter, "diameter");
    p->diameter = json_diameter->valuedouble;

    // }}}
    // get mass {{{

    cJSON *json_mass = cJSON_GetObjectItem(json_particle, "mass");
    CHECKJSON(json_mass, "mass");
    p->mass = json_mass->valuedouble;

    // }}}
    // get id {{{

    cJSON *json_id = cJSON_GetObjectItem(json_particle, "id");
    CHECKJSON(json_id, "id");
    p->id = json_id->valueint;

    // }}}

    add_particle(s, p);
  }

  free(json_str);
  
  return s;
}

// vim: ft=c foldmethod=marker
