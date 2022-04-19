#ifndef E_ASSERT_H
#define E_ASSERT_H

#include <stdbool.h>

#if defined(__TMS320C28XX__)
# define e_assert_break ({ __asm("  ESTOP0"); })
# define e_assert_break_false ({ e_assert_break, false; })
#endif

#if defined(__PPC__) && defined (__VLE__)
# define e_assert_break ({ __asm__ ("se_illegal \n\t se_nop "); })
# define e_assert_break_false ({ e_assert_break, false; })
#endif

#ifdef __MICROBLAZE__
# define e_assert_break ({ __asm__ ("brki r0,0x18"); })
# define e_assert_break_false ({ e_assert_break, false; })
#endif

#ifdef __aarch64__
# define e_assert_break ({ __asm__ ("brk 0"); })
# define e_assert_break_false ({ e_assert_break, false; })
#endif

#ifdef __ARM_ARCH
# define e_assert_break ({ __asm__ ("bkpt"); })
# define e_assert_break_false ({ e_assert_break, false; })
#endif

#ifndef e_assert_break /* default: x86 */
# ifdef __GNUC__
#  define e_assert_break ({ __asm__("int3"); })
#  define e_assert_break_false ({ e_assert_break, false; })
# endif /* __GNUC__ */

# ifdef _MSC_VER
#  define e_assert_break __debugbreak()
#  define e_assert_break_false msvc_e_assert_break_false()
static inline bool msvc_e_assert_break_false(void)
{
    e_assert_break;
    return false;
}
# endif /* _MSC_VER */
#endif /* e_assert_break */

/* Splint */
#if defined(S_SPLINT_S)
/*@noreturnwhenfalse@*/ bool e_assert( /*@sef@*/ bool pred);
/*@noreturnwhenfalse@*/ void e_assert_void( /*@sef@*/ bool pred);
/*@maynotreturn@*/ void e_assert_fail(void);

#else

/* -DNDEBUG */
# if defined(NDEBUG)
/* -DNCHECK */
#  if defined(NCHECK)
#   define e_assert(x) (true)
#  else
#   define e_assert(x) (x)
#  endif /* -DNCHECK */

#  define e_assert_void(x)
#  define e_assert_fail()

# else

#  define e_assert(x) ((x) ? true : e_assert_break_false)
#  define e_assert_void(x) ((x) ? (void)0 : e_assert_break)
#  define e_assert_fail() e_assert_break

# endif /* -DNDEBUG */
#endif /* S_SPLINT_S */

#endif
