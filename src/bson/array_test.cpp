#include "unittest.hpp"
#include "document.hpp"
#include "element.hpp"

using namespace bson;
using namespace std;

TEST(Array, SimpleInline) {
  Array a(1, 2, "three");

  ASSERT_EQUALS(a[0],     1);
  ASSERT_EQUALS(a[1],     2);
  ASSERT_EQUALS(a[2],     "three");
  ASSERT_NOT_EQUALS(a[0], 0);
}

TEST(Array, SimpleAppend) {
  Array a;
  a.append(1);
  a.append(2);
  a.append("three");

  ASSERT_EQUALS(a[0],     1);
  ASSERT_EQUALS(a[1],     2);
  ASSERT_EQUALS(a[2],     "three");
  ASSERT_NOT_EQUALS(a[0], 0);
}

TEST(Array, NestedInline) {
  Array a(1, 2, "three", Array("Sub1", "Sub2", 3));

  ASSERT_EQUALS(a[0],        1);
  ASSERT_EQUALS(a[1],        2);
  ASSERT_EQUALS(a[2],        "three");
  ASSERT_EQUALS(a[3][0],     "Sub1");
  ASSERT_EQUALS(a[3][1],     "Sub2");
  ASSERT_EQUALS(a[3][2],     3);
  ASSERT_NOT_EQUALS(a[0],    0);
  ASSERT_NOT_EQUALS(a[3][2], 0);

}