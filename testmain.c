#include <check.h>
#include <stdio.h>

#include "basic.h"

START_TEST(test_parseLine) {
    char* instr;
    char in[MAX_LINE_LEN + 1];
    uint16_t no;

    strncpy(in, "10 print \"hoge\"", sizeof(in) / sizeof(in[0]));
    no = parseLine(in, sizeof(in), &instr);

    ck_assert_int_eq(10, no);
    ck_assert_str_eq("print \"hoge\"", instr);

    strncpy(in, "20 goto 30", sizeof(in) / sizeof(in[0]));
    no = parseLine(in, sizeof(in), &instr);

    ck_assert_int_eq(20, no);
    ck_assert_str_eq("goto 30", instr);
}
END_TEST

START_TEST(test_upsertLine) {
    char in[] = "print \"hoge\"";
    uint16_t want1 = 10; // lineno
    uint8_t want1l = 12; // line len
    char want1s[] = "print \"hoge\"";

    char in2[] = "a=3";
    uint16_t want2 = 20; // lineno
    uint8_t want2l = 3;  // line len
    char want2s[] = "a=3";

    char in3[] = "print 42";
    char in3b[] = "print 421";
    char in3c[] = "b=2";
    uint16_t want3 = 15; // lineno
    uint8_t want3l = 8;  // line len
    uint8_t want3lb = 9; // line len
    uint8_t want3lc = 3; // line len
    char want3s[] = "print 42";
    char want3sb[] = "print 421";
    char want3sc[] = "b=2";

    resetLines();

    upsertLine(10, in);
    ck_assert_mem_eq(&want1, &lines[0], 2);
    ck_assert_mem_eq(&want1l, &lines[2], 1);
    ck_assert_mem_eq(want1s, &lines[3], strlen(want1s));
    ck_assert_int_eq(3 + want1l, szLines);

    upsertLine(20, in2);
    ck_assert_mem_eq(&want2, &lines[15], 2);
    ck_assert_mem_eq(&want2l, &lines[17], 1);
    ck_assert_mem_eq(want2s, &lines[18], strlen(want2s));
    ck_assert_int_eq(3 * 2 + want1l + want2l, szLines);
    printf("\n");

    // insert in the middle
    upsertLine(15, in3);
    ck_assert_mem_eq(&want3, &lines[15], 2);
    ck_assert_mem_eq(&want3l, &lines[17], 1);
    ck_assert_mem_eq(want3s, &lines[18], strlen(want3s));
    ck_assert_int_eq(3 * 3 + want1l + want2l + want3l, szLines);
    ck_assert_mem_eq(&want2, &lines[26], 2);
    ck_assert_mem_eq(&want2l, &lines[28], 1);

    // update the line (longer, expand)
    upsertLine(15, in3b);
    ck_assert_mem_eq(&want3, &lines[15], 2);
    ck_assert_mem_eq(&want3lb, &lines[17], 1);
    ck_assert_mem_eq(want3sb, &lines[18], strlen(want3sb));
    ck_assert_int_eq(3 * 3 + want1l + want2l + want3lb, szLines);
    ck_assert_mem_eq(&want2, &lines[27], 2);
    ck_assert_mem_eq(&want2l, &lines[29], 1);

    // update the line (shorter, shrink)
    upsertLine(15, in3c);
    ck_assert_mem_eq(&want3, &lines[15], 2);
    ck_assert_mem_eq(&want3lc, &lines[17], 1);
    ck_assert_mem_eq(want3sc, &lines[18], strlen(want3sc));
    ck_assert_int_eq(3 * 3 + want1l + want2l + want3lc, szLines);
    ck_assert_mem_eq(&want2, &lines[21], 2);
    ck_assert_mem_eq(&want2l, &lines[23], 1);
}
END_TEST

START_TEST(test_linePos) {
    resetLines();

    uint8_t len = 0;
    uint8_t* pos = linePos(10, &len);

    ck_assert_int_eq(0, len);
    ck_assert_ptr_null(pos);

    char in[] = "print \"hoge\"";
    upsertLine(10, in);
    upsertLine(20, in);

    pos = linePos(20, &len);
    ck_assert_int_eq(12, len);
    ck_assert_ptr_nonnull(pos);

    pos = linePos(10, &len);
    ck_assert_int_eq(12, len);
    ck_assert_ptr_nonnull(pos);

    pos = linePos(30, &len);
    ck_assert_ptr_null(pos);
}
END_TEST

START_TEST(test_skipSpaces) {
    char buf[] = "   foo";
    uint8_t len = strlen(buf);

    uint16_t offset = 0;

    skipSpaces(buf, len, &offset);
    ck_assert_int_eq(3, offset);
}
END_TEST

START_TEST(test_getToken) {
    char buf[] = "print 10";
    uint8_t len = strlen(buf);

    uint16_t offset = 0;
    token tok;

    tok = getToken(buf, len, &offset, false);

    ck_assert_int_eq(5, offset);
    ck_assert_int_eq(0, tok.offset);
    ck_assert_int_eq(5, tok.len);
    ck_assert_int_eq(tkPrint, tok.type);

    char bufErr[] = "???";
    offset = 0;
    tok = getToken(bufErr, 3, &offset, false);
    ck_assert_int_eq(tkError, tok.type);
}
END_TEST

START_TEST(test_consume) {
    char buf[] = "if a-3 goto 30";
    uint8_t len = strlen(buf);

    uint16_t offset = 0;
    bool ret;

    ret = consume(tkIf, buf, len, &offset);
    ck_assert_int_eq(true, ret);
    ck_assert_int_eq(2, offset);

    ret = consume(tkPrint, buf, len, &offset);
    ck_assert_int_eq(false, ret);
    ck_assert_int_eq(3, offset);

    ret = consume(tkIdent, buf, len, &offset);
    ck_assert_int_eq(true, ret);
    ck_assert_int_eq(4, offset);

    ret = consume(tkSub, buf, len, &offset);
    ck_assert_int_eq(true, ret);
    ck_assert_int_eq(5, offset);

    ret = consume(tkNumber, buf, len, &offset);
    ck_assert_int_eq(true, ret);
    ck_assert_int_eq(6, offset);

    ret = consume(tkGoto, buf, len, &offset);
    ck_assert_int_eq(true, ret);
    ck_assert_int_eq(11, offset);
}
END_TEST

Suite* basic_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Basic");
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_parseLine);
    tcase_add_test(tc_core, test_upsertLine);
    tcase_add_test(tc_core, test_linePos);
    tcase_add_test(tc_core, test_skipSpaces);
    tcase_add_test(tc_core, test_getToken);
    tcase_add_test(tc_core, test_consume);
    suite_add_tcase(s, tc_core);

    return s;
}

int main() {
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = basic_suite();
    sr = srunner_create(s);

    /* srunner_run_all(sr, CK_NORMAL); */
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

