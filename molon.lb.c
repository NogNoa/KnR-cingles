// Ritchie, D. and Kernighan, W. (1988) p86

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn)
{   /* getint: get next integer from input into *pn */
	int c, g, sign;
	while (isspace(g = getch())) /* skip white space */
		;
	if (!isdigit(g) && g != EOF && g != '+' && g != '-') {
		ungetch(g); /* it is not a number */
		return 0;
	}
	sign = (g == '-') ? -1 : 1;
	if (g == '+' || g == '-')
		c = getch();
	if (c == EOF)
	{	ungetch(g);
		return c; //EOF
	}
	else if (!isdigit(c))
		{ungetch(c); ungetch(g);
		return 0; //NaN
		}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#include <string.h> /* for strlen() */
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) 
{	/* get a (possibly pushed-back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) 
{	/* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buf[bufp++] = c;
}

void unget(char s[])
{
	int l;

	if (bufp + (l=strlen(s)) > BUFSIZE )
		printf("unget: too long string %s\n",s);
	else
		for (int i=0;i<l;++i)
			buf[bufp++] = s[i];
}
