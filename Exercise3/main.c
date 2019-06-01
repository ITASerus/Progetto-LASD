
#include "utility.h"
#include "testBST.h"
#include "testGraph.h"

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

#include "graph/graph.h"
#include "graph/rec/graphrec.h"
#include "graph/itr/graphitr.h"
#include "graph/rep/mat/graphmat.h"
#include "graph/rep/lst/graphlst.h"
#include "graph/rep/bst/graphbst.h"

/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  /* ************************************************************************ */

  testGraph();

  /* ************************************************************************ */

  return 0;
}
