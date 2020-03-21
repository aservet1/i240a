#ifndef OUT_HH_
#define OUT_HH_

#include <vector>

/** Output a line containing "FOUND" if arg is found in [begin, end),
 *  otherwise output "NOT FOUND"..
 */
template <typename Iterator>
void loopFn(Iterator begin, Iterator end, int arg) {
  bool found = false;
  for (Iterator i = begin; i != end; ++i) {
    if (*i == arg) {
      found = true;
      break;
    }
  }
  if (found) printf("FOUND\n");
  else printf("NOT FOUND\n");
}

/** Exactly like loopFn() but no loops should be used */
template <typename Iterator>
void noLoopFn(Iterator begin, Iterator end, int arg) {
  //@TODO
  Iterator i = std::find(begin,end,arg);
  if (i != end) printf("FOUND\n");
  else printf("NOT FOUND\n");
}

#endif //ifndef OUT_HH_
