#include <stdio.h>
#include <string.h>

int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strcat(char *dest, char *src);
char		*ft_strstr(char *str, char *to_find);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

static int pass = 0;
static int fail = 0;

static void check_sign(const char *label, int got, int expected_sign)
{
	int ok = (expected_sign == 0) ? (got == 0)
	       : (expected_sign  < 0) ? (got  < 0)
	       :                        (got  > 0);
	if (ok)
		printf("[PASS] %s\n", label);
	else
	{
		printf("[FAIL] %s  got=%d\n", label, got);
		fail++;
		return;
	}
	pass++;
}

static void check_str(const char *label, const char *got, const char *expected)
{
	if (got && expected && strcmp(got, expected) == 0)
	{
		printf("[PASS] %s\n", label);
		pass++;
	}
	else if (!got && !expected)
	{
		printf("[PASS] %s\n", label);
		pass++;
	}
	else
	{
		printf("[FAIL] %s  got=\"%s\"  expected=\"%s\"\n",
			label, got ? got : "(null)", expected ? expected : "(null)");
		fail++;
	}
}

static void check_ptr(const char *label, const void *got, const void *expected)
{
	if (got == expected)
	{
		printf("[PASS] %s\n", label);
		pass++;
	}
	else
	{
		printf("[FAIL] %s  got=%p  expected=%p\n", label, got, expected);
		fail++;
	}
}

static void check_uint(const char *label, unsigned int got, unsigned int expected)
{
	if (got == expected)
	{
		printf("[PASS] %s\n", label);
		pass++;
	}
	else
	{
		printf("[FAIL] %s  got=%u  expected=%u\n", label, got, expected);
		fail++;
	}
}

/* ------------------------------------------------------------------ */
/*  ex00 – ft_strcmp                                                   */
/* ------------------------------------------------------------------ */
static void test_strcmp(void)
{
	printf("\n--- ex00: ft_strcmp ---\n");
	check_sign("equal strings",           ft_strcmp("abc", "abc"),  0);
	check_sign("s1 < s2",                 ft_strcmp("abc", "abd"), -1);
	check_sign("s1 > s2",                 ft_strcmp("abd", "abc"),  1);
	check_sign("empty == empty",          ft_strcmp("", ""),         0);
	check_sign("empty < non-empty",       ft_strcmp("", "a"),       -1);
	check_sign("non-empty > empty",       ft_strcmp("a", ""),        1);
	check_sign("prefix shorter",          ft_strcmp("ab", "abc"),   -1);
	check_sign("prefix longer",           ft_strcmp("abc", "ab"),    1);
}

/* ------------------------------------------------------------------ */
/*  ex01 – ft_strncmp                                                  */
/* ------------------------------------------------------------------ */
static void test_strncmp(void)
{
	printf("\n--- ex01: ft_strncmp ---\n");
	check_sign("n=0 always 0",            ft_strncmp("abc", "xyz", 0),  0);
	check_sign("equal within n",          ft_strncmp("abcX", "abcY", 3), 0);
	check_sign("differ within n (s1<s2)", ft_strncmp("abc", "abd", 4),  -1);
	check_sign("differ within n (s1>s2)", ft_strncmp("abd", "abc", 4),   1);
	check_sign("equal strings, n>len",    ft_strncmp("abc", "abc", 10),  0);
	check_sign("empty strings, n=5",      ft_strncmp("", "", 5),          0);
	check_sign("s1 shorter, n covers",    ft_strncmp("ab", "abc", 3),   -1);
}

/* ------------------------------------------------------------------ */
/*  ex02 – ft_strcat                                                   */
/* ------------------------------------------------------------------ */
static void test_strcat(void)
{
	char buf[64];

	printf("\n--- ex02: ft_strcat ---\n");

	strcpy(buf, "Hello, ");
	ft_strcat(buf, "world!");
	check_str("basic append",         buf, "Hello, world!");

	strcpy(buf, "");
	ft_strcat(buf, "hello");
	check_str("append to empty dest", buf, "hello");

	strcpy(buf, "hello");
	ft_strcat(buf, "");
	check_str("append empty src",     buf, "hello");

	strcpy(buf, "foo");
	char *ret = ft_strcat(buf, "bar");
	check_str("returns dest",         ret, "foobar");
	check_ptr("return ptr == dest",   ret, buf);
}

/* ------------------------------------------------------------------ */
/*  ex03 – ft_strncat  (file: strncat.c)                              */
/*  NOTE: the submitted file defines ft_strcat instead of ft_strncat. */
/*  Tests below reflect what the file actually implements.             */
/* ------------------------------------------------------------------ */
/* No additional tests; ex02 already covers ft_strcat.                */

/* ------------------------------------------------------------------ */
/*  ex04 – ft_strstr                                                   */
/* ------------------------------------------------------------------ */
static void test_strstr(void)
{
	char	str[] = "hello world";

	printf("\n--- ex04: ft_strstr ---\n");

	char *r = ft_strstr(str, "world");
	check_ptr("finds substring",          r, str + 6);
	check_str("content at result",        r, "world");

	check_ptr("not found returns NULL",   ft_strstr(str, "xyz"), NULL);

	r = ft_strstr(str, "");
	check_ptr("empty needle returns str", r, str);

	check_ptr("needle == haystack",       ft_strstr("abc", "abc"), str - (str - (char *)"abc"));
	/* simpler version: */
	{
		char hay[] = "abc";
		check_ptr("needle == haystack v2", ft_strstr(hay, "abc"), hay);
	}

	check_ptr("needle longer than hay",   ft_strstr("ab", "abcde"), NULL);

	{
		char hay[] = "aababc";
		char *res = ft_strstr(hay, "abc");
		check_ptr("overlapping prefix",   res, hay + 3);
	}
}

/* ------------------------------------------------------------------ */
/*  ex05 – ft_strlcat                                                  */
/* ------------------------------------------------------------------ */
static void test_strlcat(void)
{
	char buf[32];

	printf("\n--- ex05: ft_strlcat ---\n");

	/* Normal case: room to append fully */
	strcpy(buf, "hello");
	check_uint("return = dest_len+src_len",
		ft_strlcat(buf, " world", 32), 11);
	check_str("result string", buf, "hello world");

	/* size limits the copy */
	strcpy(buf, "hi");
	check_uint("truncated return value",
		ft_strlcat(buf, "12345", 6), 7);   /* 2 + 5 */
	check_str("truncated result", buf, "hi123");

	/* size == current dest length: nothing appended */
	strcpy(buf, "hello");
	unsigned int ret = ft_strlcat(buf, "world", 5);
	check_uint("size==destlen return = size+srclen", ret, 10);
	check_str("dest unchanged when size==destlen", buf, "hello");

	/* append to empty dest */
	buf[0] = '\0';
	check_uint("empty dest return", ft_strlcat(buf, "abc", 10), 3);
	check_str("empty dest result",  buf, "abc");

	/* empty src */
	strcpy(buf, "hello");
	check_uint("empty src return", ft_strlcat(buf, "", 32), 5);
	check_str("empty src dest unchanged", buf, "hello");
}

/* ------------------------------------------------------------------ */
int main(void)
{
	test_strcmp();
	test_strncmp();
	test_strcat();
	test_strstr();
	test_strlcat();

	printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
	return (fail > 0 ? 1 : 0);
}
