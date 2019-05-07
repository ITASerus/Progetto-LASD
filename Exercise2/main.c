
#include "utility.h"
#include "test.h"
#include "testBST.h"

/* ************************************************************************** */

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/rec/adtrec.h"

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "stack/lst/stacklst.h"

#include "queue/queue.h"
#include "queue/vec/queuevec.h"
#include "queue/lst/queuelst.h"

#include "bst/bst.h"
#include "bst/rec/bstrec.h"
#include "bst/itr/bstitr.h"

/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  /* ************************************************************************ */

  //testMain();
  testBST();

  /* ************************************************************************ */
  return 0;
}
