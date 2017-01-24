// Parmake
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign
#include <assert.h>
#include <stdlib.h>

#include "queue.h"
#include "rule.h"

/**
 * Initializes Rule data structure.
 *
 * @param rule A pointer to the rule data structure.
 * @return Void.
 */
void rule_init(rule_t *rule) {
  assert(rule != NULL);
  rule->target = NULL;

  rule->deps = (queue_t*) malloc(sizeof(queue_t));
  queue_init(rule->deps);

  rule->commands = (queue_t*) malloc(sizeof(queue_t));
  queue_init(rule->commands);
}

/**
 * Destroys Rule data structure.
 *
 * @param rule A pointer to the rule data structure.
 * @return Void.
 */
void rule_destroy(rule_t *rule) {
  queue_destroy(rule->deps);
  free(rule->deps);

  queue_destroy(rule->commands);
  free(rule->commands);
}
