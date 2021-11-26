#ifndef E_ASSERT_H
#define E_ASSERT_H

#include <stdbool.h>

#if defined(__PPC64__) || defined(__PPC__)
# define e_assert_break ({ __asm__ ("se_illegal"); __asm__("nop"); })
#endif

#ifdef __MICROBLAZE__
# define e_assert_break ({ __asm__ ("brki r0,0x18"); })
#endif

#ifdef __aarch64__
# define e_assert_break ({ __asm__ ("brk 0"); })
#endif

#ifndef e_assert_break /* default: x86 */
# define e_assert_break ({ __asm__ ("int3"); })
#endif

#define e_assert_break_false ({ e_assert_break, false; })

/*
 * Traps are deactivated in release & unit_test builds
 */
#if defined(NDEBUG) || defined(S_SPLINT_S)

# define e_assert(x) (x)
# define e_assert_void(x) /*@-noeffect@*/
# define e_assert_fail() /*@-noeffect@*/

#else

# define e_assert(x) ((x) ? true : e_assert_break_false)
# define e_assert_void(x) /*@-noeffect@*/((x) ? (void)0 : e_assert_break)
# define e_assert_fail() /*@-noeffect@*/e_assert_break

#endif

#endif
