
#include "utility.h"

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

#include "test.h"

/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  testMain();

  return 0;
}
