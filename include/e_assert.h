#ifndef E_ASSERT_H
#define E_ASSERT_H

#include <stdbool.h>

#if defined(__PPC64__) || defined(__PPC__)
# define __break ({ __asm__ ("tw 31,r0,r0"); })
#endif

#ifdef __MICROBLAZE__
# define __break ({ __asm__ ("brki r0,0x18"); })
#endif

#ifdef __aarch64__
# define __break ({ __asm__ ("brk 0"); })
#endif

#ifndef __break /* default: x86 */
# define __break ({ __asm__ ("int3"); })
#endif

#define __break_false ({ __break, false; })

/*
 * Traps are deactivated in release & unit_test builds
 */
#if defined(NDEBUG) || defined(UNIT_TESTS)

# define e_assert(x) (x)
# define e_assert_void(x) /*@-noeffect@*/
# define e_assert_fail() /*@-noeffect@*/

#else

# define e_assert(x) ((x) ? true : __break_false)
# define e_assert_void(x) /*@-noeffect@*/((x) ? (void)0 : __break)
# define e_assert_fail() /*@-noeffect@*/__break

#endif

#endif
