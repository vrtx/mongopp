#include <iostream>

#include "unittest.hpp"
#include "document.hpp"
#include "element.hpp"

using namespace std;
using namespace bson;

TEST(Document, SimpleInline) {
  Document d("a", 1,
             "b", 2,
             "c", "three");
  ASSERT_EQUALS(d["a"],        1);
  ASSERT_EQUALS(d["b"],        2);
  ASSERT_EQUALS(d["c"], "three");
  ASSERT_NOT_EQUALS(d["a"],    0);
}

TEST(Document, SimpleAppend) {
  Document d;
  d["a"] = 1;
  d["b"] = 2;
  d["c"] = "three";
  ASSERT_EQUALS(d["a"],        1);
  ASSERT_EQUALS(d["b"],        2);
  ASSERT_EQUALS(d["c"], "three");
  ASSERT_NOT_EQUALS(d["a"],    0);
}

TEST(Document, Nested) {
    Document d;
    d["a"] = 1;
    d["b"] = 2;
    d["c"] = Document("c.a", 3);
    d["d"] = Document("d.a", 4);
    d["e"] = Document("e.a", Document("e.a.a", "5"));
    d["f"] = Document("f.a", Document("f.a.a", 5,
                                      "f.a.b", "six",
                                      "f.a.c", Document("f.a.c.a", 7),
                                      "f.a.d", Document("deep", Document("deep",
                                               Document("deep", Document("deep",
                                               Document("deep", Document("deep",
                                               Document("deep", Document("deep",
                                               Document("deep", Document("deep",
                                               Document("deep", Document("deep", Document("deep", "seven")))))))))))))),
                      "f.b", "eight");
    d["g"] = "xyz";
    ASSERT_EQUALS(d["a"], 1);
    ASSERT_EQUALS(d["b"], 2);
    ASSERT_EQUALS(d["c"]["c.a"], 3);
    ASSERT_EQUALS(d["d"]["d.a"], 4);
    ASSERT_EQUALS(d["e"]["e.a"]["e.a.a"], "5");
    ASSERT_EQUALS(d["f"]["f.a"]["f.a.a"], 5);
    ASSERT_EQUALS(d["f"]["f.a"]["f.a.b"], "six");
    ASSERT_EQUALS(d["f"]["f.a"]["f.a.c"]["f.a.c.a"], 7);
    ASSERT_EQUALS(d["f"]["f.a"]["f.a.d"]["deep"]["deep"]["deep"]["deep"]["deep"]["deep"]["deep"]
                                        ["deep"]["deep"]["deep"]["deep"]["deep"]["deep"], "seven");
    ASSERT_EQUALS(d["f"]["f.b"], "eight");
    ASSERT_EQUALS(d["g"], "xyz");
}
