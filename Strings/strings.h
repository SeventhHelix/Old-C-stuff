

struct string {
   int len;
   char * str;
};


struct string *strRead();
struct string *strNew(char *s);
struct string *strCpy(struct string *dst, struct string *src);
int strCmp(struct string *s1, struct string *s2);
struct string *strAppend(struct string *s1, struct string *s2);
struct string *strReplace(struct string *text, struct string *pat, struct string *repl);
void strFree(struct string *s);
