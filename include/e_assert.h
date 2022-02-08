#ifndef E_ASSERT_H
#define E_ASSERT_H

#include <stdbool.h>

#if defined(__PPC__) && defined (__VLE__)
# define e_assert_break ({ __asm__ ("se_illegal \n\t se_nop "); })
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

/*@maynotreturn@*/ bool e_assert( /*@sef@*/ bool pred);
/*@maynotreturn@*/ void e_assert_void( /*@sef@*/ bool pred);
/*@maynotreturn@*/ void e_assert_fail(void);

#else

# define e_assert(x) ((x) ? true : e_assert_break_false)
# define e_assert_void(x) ((x) ? (void)0 : e_assert_break)
# define e_assert_fail() e_assert_break

#endif

#endif
