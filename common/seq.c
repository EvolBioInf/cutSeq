#include "seq.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
Seq *newSeq(char *name) {
  Seq *s = (Seq *)emalloc(sizeof(Seq));
  int l = strlen(name);
  if (name[l - 1] == '\n')
    name[l - 1] = '\0';
  if (name[0] == '>')
    name++;
  s->name = estrdup(name);
  s->data = NULL;
  s->l = 0;
  return s;
}
void freeSeq(Seq *s) {
  free(s->data);
  free(s->name);
  free(s);
}
Seq *getJoinedSeq(char *fileName) {
  char *p = strrchr(fileName, '.');
  if (p)
    p = '\0';
  Seq *seq = newSeq(fileName);
  char *line = NULL;
  ssize_t nread;
  size_t len = 0, maxLen = 0;
  FILE *fp = efopen(fileName, "r");
  while ((nread = getline(&line, &len, fp)) != -1) {
    if (line[0] == '>')
      continue;
    if (line[nread - 1] == '\n')
      nread--;
    if (seq->l + nread > maxLen) {
      maxLen = 2 * (seq->l + nread);
      seq->data = erealloc(seq->data, maxLen);
    }
    for (int i = 0; i < nread; i++)
      seq->data[seq->l++] = line[i];
  }
  fclose(fp);
  free(line);
  seq->data = erealloc(seq->data, seq->l + 1);
  seq->data[seq->l] = '\0';
  return seq;
}
Seq *getSeq(FILE *fp) {
  Seq *seq = NULL;
  static char *line = NULL;
  ssize_t nread;
  static size_t len = 0;
  size_t maxLen = 0;
  if (line) {
    if (line[0] == '>') {
      seq = newSeq(line);
    } else {
      free(line);
      line = NULL;
      len = 0;
      return NULL;
    }
  }
  while ((nread = getline(&line, &len, fp)) != -1) {
    if (line[0] == '>') {
        if (seq) {
          seq->data = erealloc(seq->data, seq->l + 1);
          seq->data[seq->l] = '\0';
          return seq;
        } else
          seq = newSeq(line);
    } else {
        if (line[nread - 1] == '\n')
          nread--;
        if (seq->l + nread > maxLen) {
          maxLen = 2 * (seq->l + nread);
          seq->data = erealloc(seq->data, maxLen);
        }
        for (int i = 0; i < nread; i++)
          seq->data[seq->l++] = line[i];
    }
  }
  seq->data = erealloc(seq->data, seq->l + 1);
  seq->data[seq->l] = '\0';
  return seq;
}
void printSeq(FILE *fp, Seq *s, int l) {
  fprintf(fp, ">%s\n", s->name);
  if (l <= 0)
    l = DEFAULT_LINE_LEN;
  for (int i = 0; i < s->l; i++) {
    fprintf(fp, "%c", s->data[i]);
    if ((i + 1) % l == 0)
      fprintf(fp, "\n");
  }
  if (s->l % l)
    fprintf(fp, "\n");
}
Seq *revCmpSeq(Seq *s) {
  Seq *n;
  n = newSeq(s->name);
  n->name = erealloc(n->name, strlen(n->name) + 8);
  strncat(n->name, "_revCmp", 7);
  n->data = emalloc(s->l);
  for (int i = s->l - 1; i >= 0; i--)
    n->data[n->l++] = s->data[i];
  char dic[UCHAR_MAX];
  char *nuc = NUC_STR;
  char *cmp = CMP_STR;
  for (int i = 0; i < UCHAR_MAX; i++)
    dic[i] = 0;
  for (int i = 0; i < strlen(nuc); i++)
    dic[(int)nuc[i]] = cmp[i];
  char c;
  for (int i = 0; i < n->l; i++)
    if ((c = dic[(int)n->data[i]]) != 0)
      n->data[i] = c;
    else
      error("can't complement %c\n", c);
  return n;
}
Seq *catSeq(Seq *s1, Seq *s2) {
  char *newName;
  newName = emalloc(strlen(s1->name) + strlen(s2->name) + 2);
  newName[0] = '\0';
  strcat(newName, s1->name);
  strcat(newName, "_");
  strcat(newName, s2->name);
  Seq *n = newSeq(newName);
  free(newName);
  n->data = emalloc(s1->l + s2->l + 1);
  for (int i = 0; i < s1->l; i++)
    n->data[n->l++] = s1->data[i];
  for (int i = 0; i < s2->l; i++)
    n->data[n->l++] = s2->data[i];
  n->data[n->l] = '\0';
  return n;
  return n;
}
