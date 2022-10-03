#ifndef E_ASSERT_H
#define E_ASSERT_H

#include <stdbool.h>

#if defined(__TMS320C28XX__)
# define e_assert_break ({ __asm("  ESTOP0"); })
#endif

#if defined(__PPC__) && defined (__VLE__)
# define e_assert_break ({ __asm__ ("se_illegal \n\t se_nop "); })
#endif

#ifdef __MICROBLAZE__
# define e_assert_break ({ __asm__ ("brki r0,0x18"); })
#endif

#ifdef __aarch64__
# define e_assert_break ({ __asm__ ("brk 0"); })
#endif

#ifdef __ARM_ARCH
# define e_assert_break ({ __asm__ ("bkpt"); })
#endif

/* default: x86 */
#ifndef e_assert_break
# ifdef __GNUC__
#  define e_assert_break ({ __asm__("int3"); })
# endif /* __GNUC__ */

# ifdef _MSC_VER
#  define e_assert_break __debugbreak()
# endif /* _MSC_VER */
#endif /* e_assert_break */

/* Splint */
#ifdef S_SPLINT_S
/*@noreturnwhenfalse@*/ bool e_assert( /*@sef@*/ bool pred);
/*@noreturnwhenfalse@*/ void e_assert_void( /*@sef@*/ bool pred);
/*@maynotreturn@*/ void e_assert_fail(void);
#else

# ifdef NDEBUG /* -DNDEBUG */
#  ifdef NCHECK /* -DNCHECK */
#   define e_assert(x) (true)
#  else
#   define e_assert(x) (x)
#  endif /* -DNCHECK */

#  define e_assert_void(x)
#  define e_assert_fail()

# else

#  define e_assert(x) ((x) ? (true) : (e_assert_break, false))
#  define e_assert_void(x) if(!(x)) e_assert_break
#  define e_assert_fail() e_assert_break

# endif /* -DNDEBUG */
#endif /* S_SPLINT_S */

#endif
