
/*-----------------------------------------------------------------------*\
 |  file: Bicycle_Methods.cc                                             |
 |                                                                       |
 |  version: 1.0   date 28/11/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Bicycle.hh"
#include "Bicycle_Pars.hh"

using namespace std;
using namespace MechatronixLoad;



#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-variable"
#elif __llvm__
#pragma GCC diagnostic ignored "-Wunused-variable"
#else
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif



namespace BicycleDefine {


  //  ___   _   ___
  // |   \ /_\ | __|
  // | |) / _ \| _|
  // |___/_/ \_\___|
  //
  void
  Bicycle::get_initial_conditions(
    real_type zeta__,
    real_type result__[]
  ) const {
    result__[ 0   ] = ModelPars[26];
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::rhs_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type const U__[],
    real_type       result__[]
  ) const {
    real_type t1   = ModelPars[20];
    real_type t2   = X__[2];
    real_type t3   = t2 * t1;
    real_type t4   = X__[3];
    real_type t5   = cos(t4);
    real_type t6   = X__[7];
    real_type t7   = t6 * t5;
    real_type t8   = ModelPars[16];
    real_type t13  = X__[0];
    real_type t14  = t13 * t13;
    real_type t16  = U__[2];
    real_type t17  = U__[1];
    result__[ 0   ] = 2 * t8 * t7 * t3 - t14 * ModelPars[19] + t16 + t17;
    real_type t18  = t6 * t6;
    real_type t19  = sin(t4);
    real_type t20  = t19 * t18;
    real_type t23  = X__[6];
    real_type t24  = X__[5];
    real_type t25  = X__[4];
    real_type t26  = ModelPars[13];
    real_type t27  = cos(t26);
    real_type t29  = 1.0 / t5;
    result__[ 1   ] = t16 * t29 * t27 * t25 + t1 * t8 * t20 - t13 * t3 + t23 + t24;
    real_type t33  = t25 * t5;
    real_type t34  = ModelPars[11];
    real_type t35  = t34 * t16;
    real_type t37  = X__[8];
    real_type t39  = sin(t26);
    real_type t41  = ModelPars[22];
    real_type t42  = 1.0 / t41;
    real_type t43  = t13 * t42;
    real_type t44  = ModelPars[17];
    real_type t45  = t44 * t43;
    real_type t47  = t2 * t5;
    real_type t48  = ModelPars[6];
    real_type t50  = t27 * t27;
    real_type t67  = ModelPars[12];
    real_type t69  = ModelPars[27];
    real_type t74  = t19 * t27 * t6;
    real_type t76  = -t44 * t19 * t43 * t39 * t6 * t25 + 2 * t19 * t50 * t6 * t48 * t47 + t45 * t39 * t37 * t5 + t8 * t19 * t16 + t8 * t17 * t19 - t19 * t18 * ModelPars[5] + t74 * t48 * t37 - t67 * t23 + t69 * t23 - t24 * t67 + t35 * t33;
    real_type t79  = t44 * t19 * t27;
    real_type t84  = ModelPars[18];
    real_type t88  = t13 / ModelPars[23] * t84;
    real_type t92  = t13 * t42 * t6;
    real_type t107 = t19 * t6;
    real_type t114 = t25 * t29;
    real_type t115 = t27 * t16;
    real_type t120 = t44 * t27 * t18 * t33 - 2 * t19 * t6 * ModelPars[8] * t47 + 2 * t19 * t6 * ModelPars[9] * t47 + t39 * t48 * t27 * t20 - 2 * t44 * t107 * t47 - 2 * t84 * t107 * t47 - t67 * t115 * t114 + t69 * t115 * t114 + t79 * t6 * t37 + t92 * t44 * t5 + t88 * t7;
    result__[ 2   ] = t76 + t120;
    real_type t122 = ModelPars[15];
    real_type t123 = t1 * t122;
    real_type t125 = 1.0 / t69;
    real_type t127 = t5 * t125 * t25;
    real_type t129 = t123 * t67 * t34;
    real_type t131 = t8 * t35;
    real_type t134 = t8 * t17 * t34;
    result__[ 3   ] = -t8 * t27 * t16 * t25 - t5 * t43 * t44 * t2 + t123 * t8 * t19 - t8 * t5 * t23 - t8 * t24 * t5 - t45 * t37 * t27 + t129 * t127 - t131 * t127 - t134 * t127 - t88 * t47;
    real_type t152 = t19 * t125;
    real_type t154 = t122 * t67;
    real_type t160 = t41 * t8;
    real_type t161 = t160 * t16 * t50;
    real_type t164 = t160 * t17 * t50;
    real_type t166 = t34 * t39;
    real_type t173 = t125 * t114;
    real_type t177 = t34 * t5;
    real_type t184 = t50 * t125;
    real_type t187 = t41 * t1 * t154;
    result__[ 4   ] = t44 * t18 * t50 * t25 + t1 * t154 * t34 * t152 - t45 * t39 * t47 - t161 * t127 - t164 * t127 - t8 * t16 * t166 * t127 - t8 * t17 * t166 * t127 + t161 * t173 + t164 * t173 + U__[0] - t23 * t177 - t37 * ModelPars[0] + t129 * t39 * t125 * t33 + t187 * t184 * t33 - t187 * t184 * t114 - t131 * t152 - t134 * t152 + t92 * t44 * t27 + t74 * t48 * t2 - t79 * t6 * t2;
    real_type t202 = ModelPars[3];
    real_type t206 = X__[1];
    result__[ 5   ] = ModelPars[4] * t4 * t13 + t67 * t202 * t2 - t24 * t13 - t202 * t206;
    real_type t208 = ModelPars[2];
    real_type t212 = ModelPars[1];
    real_type t216 = t25 * t13;
    real_type t224 = t2 * t212;
    result__[ 6   ] = -t34 * t107 * t212 * t25 + t27 * t29 * t212 * t216 + t4 * t208 * t13 + t177 * t212 * t37 + t39 * t208 * t216 - t23 * t13 - t206 * t212 + t67 * t224 - t69 * t224;
    result__[ 7   ] = -t6;
    result__[ 8   ] = -t37;
    if ( m_debug )
      Mechatronix::check( result__, "rhs", 9 );
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::closed_loop_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type       result__[]
  ) const {
    real_type t6   = sin(2 * 0.3141592654e1 * ModelPars[14] * zeta__);
    result__[ 0   ] = t6 * ModelPars[25];
    result__[ 1   ] = ModelPars[10];
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check( result__, "closed_loop", 3 );
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::DrhsDx_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type const U__[],
    real_type       result__[]
  ) const {
    real_type t2   = X__[0];
    result__[ 0   ] = -2 * t2 * ModelPars[19];
    real_type t5   = ModelPars[20];
    real_type t6   = X__[3];
    real_type t7   = cos(t6);
    real_type t9   = X__[7];
    real_type t10  = ModelPars[16];
    result__[ 1   ] = 2 * t10 * t9 * t7 * t5;
    real_type t13  = X__[2];
    real_type t14  = t13 * t5;
    real_type t15  = sin(t6);
    real_type t16  = t9 * t15;
    result__[ 2   ] = -2 * t10 * t16 * t14;
    real_type t20  = t10 * t7;
    result__[ 3   ] = 2 * t20 * t14;
    result__[ 4   ] = -t14;
    result__[ 5   ] = -t2 * t5;
    real_type t23  = t9 * t9;
    real_type t24  = t7 * t23;
    real_type t25  = t5 * t10;
    real_type t27  = X__[4];
    real_type t28  = ModelPars[13];
    real_type t29  = cos(t28);
    real_type t31  = t7 * t7;
    real_type t32  = 1.0 / t31;
    real_type t33  = U__[2];
    result__[ 6   ] = t15 * t33 * t32 * t29 * t27 + t25 * t24;
    real_type t37  = 1.0 / t7;
    real_type t38  = t37 * t29;
    result__[ 7   ] = t33 * t38;
    result__[ 8   ] = 1;
    result__[ 9   ] = 1;
    result__[ 10  ] = 2 * t25 * t16;
    real_type t40  = X__[8];
    real_type t42  = sin(t28);
    real_type t43  = ModelPars[22];
    real_type t44  = 1.0 / t43;
    real_type t46  = ModelPars[17];
    real_type t47  = t46 * t44 * t42;
    real_type t50  = t42 * t9 * t27;
    real_type t54  = t9 * t7;
    real_type t55  = ModelPars[18];
    real_type t57  = 1.0 / ModelPars[23];
    real_type t58  = t57 * t55;
    real_type t60  = t46 * t7;
    real_type t61  = t44 * t9;
    result__[ 11  ] = -t46 * t15 * t44 * t50 + t47 * t40 * t7 + t58 * t54 + t61 * t60;
    real_type t63  = ModelPars[6];
    real_type t65  = t29 * t29;
    real_type t69  = ModelPars[8];
    real_type t72  = ModelPars[9];
    real_type t75  = t46 * t15;
    real_type t77  = t55 * t15;
    result__[ 12  ] = 2 * t15 * t65 * t9 * t63 * t7 - 2 * t16 * t69 * t7 + 2 * t16 * t72 * t7 - 2 * t75 * t54 - 2 * t77 * t54;
    real_type t80  = t27 * t15;
    real_type t81  = ModelPars[11];
    real_type t82  = t81 * t33;
    real_type t86  = t2 * t44;
    real_type t87  = t46 * t86;
    real_type t89  = t15 * t15;
    real_type t90  = t13 * t89;
    real_type t91  = t9 * t63;
    real_type t92  = t65 * t91;
    real_type t95  = t13 * t31;
    real_type t98  = t86 * t60;
    real_type t100 = ModelPars[5];
    real_type t103 = t7 * t33;
    real_type t105 = U__[1];
    real_type t108 = t63 * t40;
    real_type t109 = t29 * t9;
    real_type t110 = t7 * t109;
    real_type t114 = t46 * t7 * t29;
    real_type t117 = t42 * t63 * t29;
    real_type t119 = t2 * t58;
    real_type t121 = -t87 * t42 * t40 * t15 + t10 * t105 * t7 - t7 * t23 * t100 + t114 * t9 * t40 + t10 * t103 + t110 * t108 + t117 * t24 - t119 * t16 - t98 * t50 - t82 * t80 - 2 * t92 * t90 + 2 * t92 * t95;
    real_type t127 = t9 * t69;
    real_type t132 = t9 * t72;
    real_type t137 = t46 * t9;
    real_type t142 = t55 * t9;
    real_type t147 = t27 * t32;
    real_type t148 = t33 * t147;
    real_type t149 = ModelPars[12];
    real_type t150 = t149 * t29;
    real_type t153 = ModelPars[27];
    real_type t154 = t153 * t29;
    real_type t157 = -t46 * t29 * t23 * t80 - t15 * t150 * t148 + t15 * t154 * t148 - t2 * t61 * t75 + 2 * t127 * t90 - 2 * t127 * t95 - 2 * t132 * t90 + 2 * t132 * t95 + 2 * t137 * t90 - 2 * t137 * t95 + 2 * t142 * t90 - 2 * t142 * t95;
    result__[ 13  ] = t121 + t157;
    real_type t162 = t46 * t15 * t2;
    real_type t164 = t29 * t46;
    real_type t166 = t33 * t37;
    result__[ 14  ] = -t162 * t44 * t42 * t9 + t81 * t103 - t150 * t166 + t154 * t166 + t164 * t24;
    result__[ 15  ] = -t149;
    result__[ 16  ] = result__[15] + t153;
    real_type t169 = t13 * t7;
    real_type t180 = t15 * t29;
    real_type t182 = t29 * t40;
    real_type t188 = t2 * t57 * t55 * t7;
    result__[ 17  ] = 2 * t46 * t109 * t27 * t7 + 2 * t15 * t65 * t63 * t169 - t162 * t44 * t42 * t27 - 2 * t15 * t9 * t100 - 2 * t15 * t69 * t169 + 2 * t15 * t72 * t169 + t180 * t108 + 2 * t117 * t16 - 2 * t75 * t169 - 2 * t77 * t169 + t75 * t182 + t188 + t98;
    real_type t204 = t87 * t42 * t7;
    real_type t205 = t180 * t91;
    real_type t206 = t75 * t109;
    result__[ 18  ] = t204 + t205 + t206;
    real_type t210 = t46 * t13;
    result__[ 19  ] = -t44 * t46 * t182 - t7 * t44 * t210 - t58 * t169;
    result__[ 20  ] = -t188 - t98;
    real_type t213 = ModelPars[15];
    real_type t214 = t5 * t213;
    real_type t216 = 1.0 / t153;
    real_type t218 = t15 * t216 * t27;
    real_type t220 = t214 * t149 * t81;
    real_type t222 = t10 * t82;
    real_type t225 = t10 * t105 * t81;
    real_type t227 = X__[6];
    real_type t230 = X__[5];
    real_type t233 = t15 * t13;
    result__[ 21  ] = t10 * t15 * t227 + t10 * t230 * t15 + t15 * t86 * t210 + t119 * t233 + t214 * t20 - t220 * t218 + t222 * t218 + t225 * t218;
    real_type t237 = t7 * t216;
    real_type t239 = t213 * t149;
    real_type t241 = t5 * t239 * t81 * t237;
    real_type t242 = t222 * t237;
    real_type t243 = t225 * t237;
    result__[ 22  ] = -t10 * t29 * t33 + t241 - t242 - t243;
    result__[ 23  ] = -t20;
    result__[ 24  ] = result__[23];
    real_type t246 = t86 * t164;
    result__[ 25  ] = -t246;
    result__[ 26  ] = t61 * t164 - t47 * t169;
    result__[ 27  ] = -t204 + t205 - t206;
    real_type t252 = t43 * t10;
    real_type t258 = t81 * t42;
    real_type t259 = t10 * t33;
    real_type t262 = t10 * t105;
    real_type t265 = t65 * t216;
    real_type t266 = t265 * t147;
    real_type t267 = t15 * t43;
    real_type t272 = t81 * t15;
    real_type t278 = t43 * t5;
    real_type t279 = t278 * t239;
    real_type t284 = t63 * t13;
    result__[ 28  ] = t241 + t87 * t42 * t233 + t252 * t33 * t65 * t218 + t252 * t105 * t65 * t218 + t259 * t258 * t218 + t262 * t258 * t218 + t267 * t259 * t266 + t267 * t262 * t266 + t227 * t272 - t220 * t42 * t216 * t80 - t279 * t265 * t80 - t15 * t278 * t239 * t266 - t242 - t243 + t110 * t284 - t114 * t9 * t13;
    real_type t290 = t65 * t237;
    real_type t291 = t43 * t259;
    real_type t293 = t43 * t262;
    real_type t295 = t42 * t237;
    real_type t299 = t65 * t216 * t37;
    result__[ 29  ] = t46 * t23 * t65 + t220 * t295 - t222 * t295 - t225 * t295 + t279 * t290 - t279 * t299 - t291 * t290 - t293 * t290 + t291 * t299 + t293 * t299;
    result__[ 30  ] = -t81 * t7;
    result__[ 31  ] = -t75 * t29 * t13 + 2 * t137 * t65 * t27 + t180 * t284 + t246;
    result__[ 32  ] = -ModelPars[0];
    real_type t313 = ModelPars[4];
    result__[ 33  ] = t313 * t6 - t230;
    real_type t315 = ModelPars[3];
    result__[ 34  ] = -t315;
    result__[ 35  ] = t149 * t315;
    result__[ 36  ] = t313 * t2;
    result__[ 37  ] = -t2;
    real_type t316 = ModelPars[2];
    real_type t318 = ModelPars[1];
    real_type t319 = t318 * t27;
    result__[ 38  ] = t42 * t316 * t27 + t6 * t316 + t38 * t319 - t227;
    result__[ 39  ] = -t318;
    result__[ 40  ] = t149 * t318 - t153 * t318;
    real_type t325 = t316 * t2;
    result__[ 41  ] = t15 * t29 * t32 * t318 * t27 * t2 - t272 * t318 * t40 - t81 * t54 * t319 + t325;
    result__[ 42  ] = -t81 * t9 * t15 * t318 + t38 * t318 * t2 + t42 * t325;
    result__[ 43  ] = result__[37];
    result__[ 44  ] = -t272 * t319;
    result__[ 45  ] = t81 * t7 * t318;
    result__[ 46  ] = -1;
    result__[ 47  ] = -1;
    if ( m_debug )
      Mechatronix::check( result__, "DrhsDx", 48 );
  }

  void
  Bicycle::DrhsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 1   ; jIndex[10] = 7   ;
    iIndex[11] = 2   ; jIndex[11] = 0   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 2   ; jIndex[15] = 5   ;
    iIndex[16] = 2   ; jIndex[16] = 6   ;
    iIndex[17] = 2   ; jIndex[17] = 7   ;
    iIndex[18] = 2   ; jIndex[18] = 8   ;
    iIndex[19] = 3   ; jIndex[19] = 0   ;
    iIndex[20] = 3   ; jIndex[20] = 2   ;
    iIndex[21] = 3   ; jIndex[21] = 3   ;
    iIndex[22] = 3   ; jIndex[22] = 4   ;
    iIndex[23] = 3   ; jIndex[23] = 5   ;
    iIndex[24] = 3   ; jIndex[24] = 6   ;
    iIndex[25] = 3   ; jIndex[25] = 8   ;
    iIndex[26] = 4   ; jIndex[26] = 0   ;
    iIndex[27] = 4   ; jIndex[27] = 2   ;
    iIndex[28] = 4   ; jIndex[28] = 3   ;
    iIndex[29] = 4   ; jIndex[29] = 4   ;
    iIndex[30] = 4   ; jIndex[30] = 6   ;
    iIndex[31] = 4   ; jIndex[31] = 7   ;
    iIndex[32] = 4   ; jIndex[32] = 8   ;
    iIndex[33] = 5   ; jIndex[33] = 0   ;
    iIndex[34] = 5   ; jIndex[34] = 1   ;
    iIndex[35] = 5   ; jIndex[35] = 2   ;
    iIndex[36] = 5   ; jIndex[36] = 3   ;
    iIndex[37] = 5   ; jIndex[37] = 5   ;
    iIndex[38] = 6   ; jIndex[38] = 0   ;
    iIndex[39] = 6   ; jIndex[39] = 1   ;
    iIndex[40] = 6   ; jIndex[40] = 2   ;
    iIndex[41] = 6   ; jIndex[41] = 3   ;
    iIndex[42] = 6   ; jIndex[42] = 4   ;
    iIndex[43] = 6   ; jIndex[43] = 6   ;
    iIndex[44] = 6   ; jIndex[44] = 7   ;
    iIndex[45] = 6   ; jIndex[45] = 8   ;
    iIndex[46] = 7   ; jIndex[46] = 7   ;
    iIndex[47] = 8   ; jIndex[47] = 8   ;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::DrhsDu_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type const U__[],
    real_type       result__[]
  ) const {
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    real_type t1   = X__[4];
    real_type t2   = ModelPars[13];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t5   = X__[3];
    real_type t6   = cos(t5);
    real_type t7   = 1.0 / t6;
    result__[ 2   ] = t7 * t4;
    real_type t8   = sin(t5);
    real_type t9   = ModelPars[16];
    result__[ 3   ] = t9 * t8;
    real_type t10  = t1 * t6;
    real_type t11  = ModelPars[11];
    real_type t13  = t1 * t7;
    real_type t17  = ModelPars[27];
    result__[ 4   ] = t17 * t3 * t13 - ModelPars[12] * t3 * t13 + t11 * t10 + result__[3];
    real_type t20  = 1.0 / t17;
    result__[ 5   ] = -t9 * t11 * t6 * t20 * t1;
    result__[ 6   ] = -t9 * t4 + result__[5];
    result__[ 7   ] = 1;
    real_type t26  = t20 * t10;
    real_type t27  = t3 * t3;
    real_type t30  = ModelPars[22] * t9 * t27;
    real_type t32  = sin(t2);
    result__[ 8   ] = -t9 * t11 * t8 * t20 - t9 * t11 * t32 * t26 + t30 * t20 * t13 - t30 * t26;
    result__[ 9   ] = result__[8];
    if ( m_debug )
      Mechatronix::check( result__, "DrhsDu", 10 );
  }

  void
  Bicycle::DrhsDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 2   ;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::A_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type       result__[]
  ) const {
    result__[ 0   ] = ModelPars[20];
    real_type t1   = X__[3];
    real_type t2   = sin(t1);
    real_type t3   = ModelPars[16];
    result__[ 1   ] = -result__[0] * t3 * t2;
    result__[ 2   ] = result__[0];
    real_type t6   = cos(t1);
    result__[ 3   ] = result__[2] * t3 * t6;
    real_type t8   = ModelPars[18];
    real_type t11  = 1.0 / ModelPars[23];
    real_type t13  = ModelPars[17];
    real_type t14  = t2 * t13;
    real_type t15  = ModelPars[22];
    real_type t16  = 1.0 / t15;
    real_type t18  = X__[4];
    real_type t19  = t18 * t6;
    real_type t20  = ModelPars[13];
    real_type t21  = sin(t20);
    result__[ 4   ] = -t13 * t16 * t21 * t19 - t11 * t8 * t2 - t16 * t14;
    real_type t25  = t6 * t6;
    real_type t26  = ModelPars[6];
    real_type t28  = cos(t20);
    real_type t29  = t28 * t28;
    real_type t31  = ModelPars[8];
    result__[ 5   ] = t29 * t26 * t25 - t13 * t25 - t31 * t25 - t8 * t25 + ModelPars[9] * t25 + t13 + t31 + t8;
    real_type t37  = t28 * t6;
    real_type t38  = t26 * t21;
    real_type t39  = t38 * t37;
    real_type t40  = t28 * t18;
    real_type t43  = ModelPars[5] * t6;
    result__[ 6   ] = -t14 * t40 + t39 - t43;
    result__[ 7   ] = t26 * t37;
    real_type t46  = 1.0 / ModelPars[27];
    real_type t48  = ModelPars[11];
    real_type t49  = t48 * t6;
    result__[ 8   ] = t8 * t49 * t46 * t11 * t18 + t13 * t49 * t46 * t16 * t18 + t13 * t16 * t40;
    result__[ 9   ] = t39 - t43;
    result__[ 10  ] = -t29 * t26 + t26 + ModelPars[7];
    result__[ 11  ] = t38;
    real_type t61  = t48 * t2;
    real_type t64  = 1.0 / t6;
    real_type t65  = t18 * t64;
    real_type t66  = t29 * t46;
    real_type t67  = t13 * t66;
    real_type t74  = t21 * t46;
    real_type t78  = t11 * t19;
    real_type t80  = t15 * t8 * t66;
    result__[ 12  ] = t13 * t48 * t74 * t16 * t19 + t8 * t61 * t46 * t11 + t13 * t61 * t46 * t16 + t8 * t48 * t74 * t78 - t80 * t11 * t65 + t67 * t19 - t67 * t65 + t80 * t78;
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = t26;
    result__[ 16  ] = ModelPars[24];
    real_type t88  = 1.0 / X__[0];
    result__[ 17  ] = result__[16] - t15 * X__[7] * t28 / t25 * result__[16] * t18 * t88 - t15 * t2 * t28 * t64 * result__[16] * X__[8] * t88;
    result__[ 18  ] = -1;
    result__[ 19  ] = -1;
    if ( m_debug )
      Mechatronix::check( result__, "A", 20 );
  }

  void
  Bicycle::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 2   ;
    iIndex[10] = 3   ; jIndex[10] = 7   ;
    iIndex[11] = 3   ; jIndex[11] = 8   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 2   ;
    iIndex[14] = 4   ; jIndex[14] = 7   ;
    iIndex[15] = 4   ; jIndex[15] = 8   ;
    iIndex[16] = 5   ; jIndex[16] = 5   ;
    iIndex[17] = 6   ; jIndex[17] = 6   ;
    iIndex[18] = 7   ; jIndex[18] = 3   ;
    iIndex[19] = 8   ; jIndex[19] = 4   ;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::DetaDx_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type const L__[],
    real_type       result__[]
  ) const {
    real_type t1   = X__[3];
    real_type t2   = cos(t1);
    real_type t3   = ModelPars[16];
    real_type t5   = ModelPars[20];
    real_type t6   = L__[2];
    result__[ 0   ] = -t6 * t5 * t3 * t2;
    real_type t9   = sin(t1);
    real_type t11  = L__[7];
    result__[ 1   ] = -t11 * t5 * t3 * t9;
    real_type t14  = ModelPars[18];
    real_type t15  = t14 * t2;
    real_type t17  = 1.0 / ModelPars[23];
    real_type t19  = ModelPars[17];
    real_type t20  = t2 * t19;
    real_type t21  = ModelPars[22];
    real_type t22  = 1.0 / t21;
    real_type t24  = X__[4];
    real_type t25  = t24 * t9;
    real_type t26  = ModelPars[13];
    real_type t27  = sin(t26);
    real_type t32  = L__[0];
    real_type t34  = ModelPars[6];
    real_type t36  = cos(t26);
    real_type t37  = t36 * t36;
    real_type t51  = t36 * t9;
    real_type t53  = t27 * t34 * t51;
    real_type t57  = ModelPars[5] * t9;
    result__[ 2   ] = t32 * (t19 * t22 * t27 * t25 - t17 * t15 - t22 * t20) + t6 * (-2 * t9 * t37 * t34 * t2 + 2 * t9 * ModelPars[8] * t2 - 2 * t9 * ModelPars[9] * t2 + 2 * t9 * t15 + 2 * t9 * t20) + t11 * (-t20 * t36 * t24 - t53 + t57) - L__[8] * t34 * t51;
    result__[ 3   ] = -t32 * t19 * t22 * t27 * t2 - t11 * t19 * t51;
    real_type t71  = 1.0 / ModelPars[27];
    real_type t73  = ModelPars[11];
    real_type t74  = t73 * t9;
    result__[ 4   ] = t32 * (-t14 * t74 * t71 * t17 * t24 - t19 * t74 * t71 * t22 * t24) + t6 * (-t53 + t57);
    real_type t86  = t73 * t2;
    real_type t88  = t19 * t86 * t71 * t22;
    real_type t89  = t71 * t17;
    real_type t91  = t14 * t86 * t89;
    result__[ 5   ] = t32 * (t19 * t22 * t36 + t88 + t91);
    real_type t95  = t2 * t2;
    real_type t96  = 1.0 / t95;
    real_type t97  = t24 * t96;
    real_type t99  = t19 * t37;
    real_type t102 = t37 * t71;
    real_type t106 = t27 * t71;
    real_type t110 = t17 * t25;
    real_type t115 = t14 * t37;
    real_type t116 = t9 * t21;
    result__[ 6   ] = t32 * (-t19 * t73 * t106 * t22 * t25 - t21 * t14 * t102 * t110 - t14 * t73 * t106 * t110 - t116 * t115 * t89 * t97 - t9 * t99 * t71 * t97 - t19 * t102 * t25 + t88 + t91) - t6 * t34 * t51;
    real_type t126 = 1.0 / t2;
    real_type t133 = t73 * t27;
    real_type t137 = t71 * t17 * t2;
    real_type t138 = t21 * t115;
    result__[ 7   ] = t32 * (t19 * t133 * t71 * t22 * t2 - t138 * t71 * t17 * t126 - t99 * t71 * t126 + t14 * t133 * t137 + t99 * t71 * t2 + t138 * t137);
    real_type t146 = X__[0];
    real_type t147 = t146 * t146;
    real_type t148 = 1.0 / t147;
    real_type t150 = ModelPars[24];
    real_type t152 = t36 * t96;
    real_type t153 = X__[7];
    real_type t157 = X__[8];
    real_type t164 = L__[6];
    result__[ 8   ] = t164 * (t116 * t36 * t126 * t150 * t157 * t148 + t21 * t153 * t152 * t150 * t24 * t148);
    real_type t165 = 1.0 / t146;
    real_type t166 = t24 * t165;
    real_type t171 = t153 * t36;
    real_type t175 = t157 * t165;
    real_type t177 = t9 * t9;
    result__[ 9   ] = t164 * (-2 * t116 * t171 / t95 / t2 * t150 * t166 - t21 * t177 * t152 * t150 * t175 - t21 * t36 * t150 * t175);
    real_type t185 = t150 * t165;
    real_type t187 = t164 * t21;
    result__[ 10  ] = -t187 * t171 * t96 * t185;
    result__[ 11  ] = -t187 * t152 * t150 * t166;
    result__[ 12  ] = -t187 * t51 * t126 * t185;
    if ( m_debug )
      Mechatronix::check( result__, "DetaDx", 13 );
  }

  void
  Bicycle::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 6   ; jIndex[9 ] = 3   ;
    iIndex[10] = 6   ; jIndex[10] = 4   ;
    iIndex[11] = 6   ; jIndex[11] = 7   ;
    iIndex[12] = 6   ; jIndex[12] = 8   ;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::Dclosed_loopDx_eval(
    real_type       zeta__,
    real_type const X__[],
    real_type       result__[]
  ) const {

    if ( m_debug )
      Mechatronix::check( result__, "Dclosed_loopDx", 0 );
  }

  void
  Bicycle::Dclosed_loopDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  //   ___ _               _        ___ _        _
  //  / __| |_ ___ __ _ __| |_  _  / __| |_ __ _| |_ ___
  //  \__ \  _/ -_) _` / _` | || | \__ \  _/ _` |  _/ -_)
  //  |___/\__\___\__,_\__,_|\_, | |___/\__\__,_|\__\___|
  //                         |__/
  void
  Bicycle::get_steady_state_default_guess(
    real_type & zeta__,
    real_type   X__[],
    real_type   U__[]
  ) const {
    X__[ 0   ] = ModelPars[26];
    X__[ 1   ] = 0;
    X__[ 2   ] = 0;
    X__[ 3   ] = 0;
    X__[ 4   ] = 0;
    X__[ 5   ] = 0;
    X__[ 6   ] = 0;
    X__[ 7   ] = 0;
    X__[ 8   ] = 0;
    U__[ 0   ] = 0;
    real_type t3   = ModelPars[26] * ModelPars[26];
    U__[ 1   ] = t3 * ModelPars[19];
    U__[ 2   ] = 0;
  }

  //
  // --------------------------------------------------------------------------
  //
  bool
  Bicycle::steady_state_equations(
    real_type       zeta__,
    real_type const Z__[],
    real_type       result__[]
  ) const {
    real_type const * X__ = Z__;
    real_type const * U__ = Z__ + numXvars;
    real_type t1   = ModelPars[20];
    real_type t2   = X__[2];
    real_type t3   = t2 * t1;
    real_type t4   = X__[3];
    real_type t5   = cos(t4);
    real_type t6   = X__[7];
    real_type t7   = t6 * t5;
    real_type t8   = ModelPars[16];
    real_type t13  = X__[0];
    real_type t14  = t13 * t13;
    real_type t16  = U__[2];
    real_type t17  = U__[1];
    result__[ 0   ] = 2 * t8 * t7 * t3 - t14 * ModelPars[19] + t16 + t17;
    real_type t18  = t6 * t6;
    real_type t19  = sin(t4);
    real_type t20  = t19 * t18;
    real_type t23  = X__[6];
    real_type t24  = X__[5];
    real_type t25  = X__[4];
    real_type t26  = ModelPars[13];
    real_type t27  = cos(t26);
    real_type t29  = 1.0 / t5;
    result__[ 1   ] = t16 * t29 * t27 * t25 + t1 * t8 * t20 - t13 * t3 + t23 + t24;
    real_type t33  = t25 * t5;
    real_type t34  = ModelPars[11];
    real_type t35  = t34 * t16;
    real_type t37  = X__[8];
    real_type t39  = sin(t26);
    real_type t41  = ModelPars[22];
    real_type t42  = 1.0 / t41;
    real_type t43  = t13 * t42;
    real_type t44  = ModelPars[17];
    real_type t45  = t44 * t43;
    real_type t47  = t2 * t5;
    real_type t48  = ModelPars[6];
    real_type t50  = t27 * t27;
    real_type t67  = ModelPars[12];
    real_type t69  = ModelPars[27];
    real_type t74  = t19 * t27 * t6;
    real_type t76  = -t44 * t19 * t43 * t39 * t6 * t25 + 2 * t19 * t50 * t6 * t48 * t47 + t45 * t39 * t37 * t5 + t8 * t19 * t16 + t8 * t17 * t19 - t19 * t18 * ModelPars[5] + t74 * t48 * t37 - t67 * t23 + t69 * t23 - t24 * t67 + t35 * t33;
    real_type t79  = t44 * t19 * t27;
    real_type t84  = ModelPars[18];
    real_type t88  = t13 / ModelPars[23] * t84;
    real_type t92  = t13 * t42 * t6;
    real_type t107 = t19 * t6;
    real_type t114 = t25 * t29;
    real_type t115 = t27 * t16;
    real_type t120 = t44 * t27 * t18 * t33 - 2 * t19 * t6 * ModelPars[8] * t47 + 2 * t19 * t6 * ModelPars[9] * t47 + t39 * t48 * t27 * t20 - 2 * t44 * t107 * t47 - 2 * t84 * t107 * t47 - t67 * t115 * t114 + t69 * t115 * t114 + t79 * t6 * t37 + t92 * t44 * t5 + t88 * t7;
    result__[ 2   ] = t76 + t120;
    real_type t122 = ModelPars[15];
    real_type t123 = t1 * t122;
    real_type t125 = 1.0 / t69;
    real_type t127 = t5 * t125 * t25;
    real_type t129 = t123 * t67 * t34;
    real_type t131 = t8 * t35;
    real_type t134 = t8 * t17 * t34;
    result__[ 3   ] = -t8 * t27 * t16 * t25 - t5 * t43 * t44 * t2 + t123 * t8 * t19 - t8 * t5 * t23 - t8 * t24 * t5 - t45 * t37 * t27 + t129 * t127 - t131 * t127 - t134 * t127 - t88 * t47;
    real_type t152 = t19 * t125;
    real_type t154 = t122 * t67;
    real_type t160 = t41 * t8;
    real_type t161 = t160 * t16 * t50;
    real_type t164 = t160 * t17 * t50;
    real_type t166 = t34 * t39;
    real_type t173 = t125 * t114;
    real_type t177 = t34 * t5;
    real_type t184 = t50 * t125;
    real_type t187 = t41 * t1 * t154;
    result__[ 4   ] = t44 * t18 * t50 * t25 + t1 * t154 * t34 * t152 - t45 * t39 * t47 - t161 * t127 - t164 * t127 - t8 * t16 * t166 * t127 - t8 * t17 * t166 * t127 + t161 * t173 + t164 * t173 + U__[0] - t23 * t177 - t37 * ModelPars[0] + t129 * t39 * t125 * t33 + t187 * t184 * t33 - t187 * t184 * t114 - t131 * t152 - t134 * t152 + t92 * t44 * t27 + t74 * t48 * t2 - t79 * t6 * t2;
    real_type t202 = ModelPars[3];
    real_type t206 = X__[1];
    result__[ 5   ] = ModelPars[4] * t4 * t13 + t67 * t202 * t2 - t24 * t13 - t202 * t206;
    real_type t208 = ModelPars[2];
    real_type t212 = ModelPars[1];
    real_type t216 = t25 * t13;
    real_type t224 = t2 * t212;
    result__[ 6   ] = -t34 * t107 * t212 * t25 + t27 * t29 * t212 * t216 + t4 * t208 * t13 + t177 * t212 * t37 + t39 * t208 * t216 - t23 * t13 - t206 * t212 + t67 * t224 - t69 * t224;
    result__[ 7   ] = -t6;
    result__[ 8   ] = -t37;
    result__[ 9   ] = t13 - ModelPars[26];
    result__[ 10  ] = t2 - ModelPars[21];
    result__[ 11  ] = t16;
    if ( m_debug )
      Mechatronix::check( result__,"steady_state_equations",12 );
    return true;
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::steady_state_DequationsDz_sparse(
    real_type       zeta__,
    real_type const Z__[],
    real_type       result__[]
  ) const {
    real_type const * X__ = Z__;
    real_type const * U__ = Z__ + numXvars;
    real_type t2   = X__[0];
    result__[ 0   ] = -2 * t2 * ModelPars[19];
    real_type t5   = ModelPars[20];
    real_type t6   = X__[3];
    real_type t7   = cos(t6);
    real_type t9   = X__[7];
    real_type t10  = ModelPars[16];
    result__[ 1   ] = 2 * t10 * t9 * t7 * t5;
    real_type t13  = X__[2];
    real_type t14  = t13 * t5;
    real_type t15  = sin(t6);
    real_type t16  = t9 * t15;
    result__[ 2   ] = -2 * t10 * t16 * t14;
    real_type t20  = t10 * t7;
    result__[ 3   ] = 2 * t20 * t14;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -t14;
    result__[ 7   ] = -t2 * t5;
    real_type t23  = t9 * t9;
    real_type t24  = t7 * t23;
    real_type t25  = t5 * t10;
    real_type t27  = X__[4];
    real_type t28  = ModelPars[13];
    real_type t29  = cos(t28);
    real_type t30  = t29 * t27;
    real_type t31  = t7 * t7;
    real_type t32  = 1.0 / t31;
    real_type t33  = U__[2];
    result__[ 8   ] = t15 * t33 * t32 * t30 + t25 * t24;
    real_type t37  = 1.0 / t7;
    real_type t38  = t37 * t29;
    result__[ 9   ] = t33 * t38;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    result__[ 12  ] = 2 * t25 * t16;
    result__[ 13  ] = t37 * t30;
    real_type t40  = X__[8];
    real_type t42  = sin(t28);
    real_type t43  = ModelPars[22];
    real_type t44  = 1.0 / t43;
    real_type t46  = ModelPars[17];
    real_type t47  = t46 * t44 * t42;
    real_type t50  = t42 * t9 * t27;
    real_type t54  = t9 * t7;
    real_type t55  = ModelPars[18];
    real_type t57  = 1.0 / ModelPars[23];
    real_type t58  = t57 * t55;
    real_type t60  = t46 * t7;
    real_type t61  = t44 * t9;
    result__[ 14  ] = -t46 * t15 * t44 * t50 + t47 * t40 * t7 + t58 * t54 + t61 * t60;
    real_type t63  = ModelPars[6];
    real_type t65  = t29 * t29;
    real_type t69  = ModelPars[8];
    real_type t72  = ModelPars[9];
    real_type t75  = t46 * t15;
    real_type t77  = t55 * t15;
    result__[ 15  ] = 2 * t15 * t65 * t9 * t63 * t7 - 2 * t16 * t69 * t7 + 2 * t16 * t72 * t7 - 2 * t75 * t54 - 2 * t77 * t54;
    real_type t80  = t27 * t15;
    real_type t81  = ModelPars[11];
    real_type t82  = t81 * t33;
    real_type t86  = t2 * t44;
    real_type t87  = t46 * t86;
    real_type t89  = t15 * t15;
    real_type t90  = t13 * t89;
    real_type t91  = t9 * t63;
    real_type t92  = t65 * t91;
    real_type t95  = t13 * t31;
    real_type t98  = t86 * t60;
    real_type t100 = ModelPars[5];
    real_type t103 = t7 * t33;
    real_type t105 = U__[1];
    real_type t108 = t63 * t40;
    real_type t109 = t29 * t9;
    real_type t110 = t7 * t109;
    real_type t114 = t46 * t7 * t29;
    real_type t117 = t42 * t63 * t29;
    real_type t119 = t2 * t58;
    real_type t121 = -t87 * t42 * t40 * t15 + t10 * t105 * t7 - t7 * t23 * t100 + t114 * t9 * t40 + t10 * t103 + t110 * t108 + t117 * t24 - t119 * t16 - t98 * t50 - t82 * t80 - 2 * t92 * t90 + 2 * t92 * t95;
    real_type t127 = t9 * t69;
    real_type t132 = t9 * t72;
    real_type t137 = t46 * t9;
    real_type t142 = t55 * t9;
    real_type t147 = t27 * t32;
    real_type t148 = t33 * t147;
    real_type t149 = ModelPars[12];
    real_type t150 = t149 * t29;
    real_type t153 = ModelPars[27];
    real_type t154 = t153 * t29;
    real_type t157 = -t46 * t29 * t23 * t80 - t15 * t150 * t148 + t15 * t154 * t148 - t2 * t61 * t75 + 2 * t127 * t90 - 2 * t127 * t95 - 2 * t132 * t90 + 2 * t132 * t95 + 2 * t137 * t90 - 2 * t137 * t95 + 2 * t142 * t90 - 2 * t142 * t95;
    result__[ 16  ] = t121 + t157;
    real_type t162 = t46 * t15 * t2;
    real_type t164 = t29 * t46;
    real_type t166 = t33 * t37;
    result__[ 17  ] = -t162 * t44 * t42 * t9 + t81 * t103 - t150 * t166 + t154 * t166 + t164 * t24;
    result__[ 18  ] = -t149;
    result__[ 19  ] = result__[18] + t153;
    real_type t169 = t13 * t7;
    real_type t180 = t15 * t29;
    real_type t182 = t29 * t40;
    real_type t188 = t2 * t57 * t55 * t7;
    real_type t189 = t27 * t7;
    result__[ 20  ] = 2 * t15 * t65 * t63 * t169 - t162 * t44 * t42 * t27 - 2 * t15 * t9 * t100 + 2 * t46 * t109 * t189 - 2 * t15 * t69 * t169 + 2 * t15 * t72 * t169 + t180 * t108 + 2 * t117 * t16 - 2 * t75 * t169 - 2 * t77 * t169 + t75 * t182 + t188 + t98;
    real_type t204 = t87 * t42 * t7;
    real_type t205 = t180 * t91;
    real_type t206 = t75 * t109;
    result__[ 21  ] = t204 + t205 + t206;
    result__[ 22  ] = t10 * t15;
    real_type t208 = t27 * t37;
    result__[ 23  ] = -t150 * t208 + t154 * t208 + t81 * t189 + result__[22];
    real_type t214 = t46 * t13;
    result__[ 24  ] = -t44 * t46 * t182 - t7 * t44 * t214 - t58 * t169;
    result__[ 25  ] = -t188 - t98;
    real_type t217 = ModelPars[15];
    real_type t218 = t5 * t217;
    real_type t220 = 1.0 / t153;
    real_type t221 = t220 * t27;
    real_type t222 = t15 * t221;
    real_type t224 = t218 * t149 * t81;
    real_type t226 = t10 * t82;
    real_type t229 = t10 * t105 * t81;
    real_type t231 = X__[6];
    real_type t234 = X__[5];
    real_type t237 = t15 * t13;
    result__[ 26  ] = t10 * t15 * t231 + t10 * t234 * t15 + t15 * t86 * t214 + t119 * t237 + t218 * t20 - t224 * t222 + t226 * t222 + t229 * t222;
    real_type t241 = t7 * t220;
    real_type t243 = t217 * t149;
    real_type t245 = t5 * t243 * t81 * t241;
    real_type t246 = t226 * t241;
    real_type t247 = t229 * t241;
    result__[ 27  ] = -t10 * t29 * t33 + t245 - t246 - t247;
    result__[ 28  ] = -t20;
    result__[ 29  ] = result__[28];
    real_type t250 = t86 * t164;
    result__[ 30  ] = -t250;
    real_type t251 = t81 * t7;
    result__[ 31  ] = -t10 * t251 * t221;
    result__[ 32  ] = -t10 * t30 + result__[31];
    result__[ 33  ] = t61 * t164 - t47 * t169;
    result__[ 34  ] = -t204 + t205 - t206;
    real_type t260 = t43 * t10;
    real_type t266 = t81 * t42;
    real_type t267 = t10 * t33;
    real_type t270 = t10 * t105;
    real_type t273 = t65 * t220;
    real_type t274 = t273 * t147;
    real_type t275 = t15 * t43;
    real_type t280 = t81 * t15;
    real_type t286 = t43 * t5;
    real_type t287 = t286 * t243;
    real_type t292 = t63 * t13;
    result__[ 35  ] = t245 + t87 * t42 * t237 + t260 * t33 * t65 * t222 + t260 * t105 * t65 * t222 + t267 * t266 * t222 + t270 * t266 * t222 + t275 * t267 * t274 + t275 * t270 * t274 + t231 * t280 - t224 * t42 * t220 * t80 - t287 * t273 * t80 - t15 * t286 * t243 * t274 - t246 - t247 + t110 * t292 - t114 * t9 * t13;
    real_type t298 = t65 * t241;
    real_type t299 = t43 * t267;
    real_type t301 = t43 * t270;
    real_type t303 = t42 * t241;
    real_type t307 = t65 * t220 * t37;
    result__[ 36  ] = t46 * t23 * t65 + t224 * t303 - t226 * t303 - t229 * t303 + t287 * t298 - t287 * t307 - t299 * t298 - t301 * t298 + t299 * t307 + t301 * t307;
    result__[ 37  ] = -t251;
    result__[ 38  ] = -t75 * t29 * t13 + 2 * t137 * t65 * t27 + t180 * t292 + t250;
    result__[ 39  ] = -ModelPars[0];
    result__[ 40  ] = 1;
    real_type t320 = t220 * t189;
    real_type t322 = t43 * t10 * t65;
    result__[ 41  ] = -t10 * t81 * t15 * t220 - t10 * t266 * t320 + t322 * t220 * t208 - t322 * t320;
    result__[ 42  ] = result__[41];
    real_type t331 = ModelPars[4];
    result__[ 43  ] = t331 * t6 - t234;
    real_type t333 = ModelPars[3];
    result__[ 44  ] = -t333;
    result__[ 45  ] = t149 * t333;
    result__[ 46  ] = t331 * t2;
    result__[ 47  ] = -t2;
    real_type t334 = ModelPars[2];
    real_type t336 = ModelPars[1];
    real_type t337 = t336 * t27;
    result__[ 48  ] = t42 * t334 * t27 + t6 * t334 + t38 * t337 - t231;
    result__[ 49  ] = -t336;
    result__[ 50  ] = t149 * t336 - t153 * t336;
    real_type t343 = t334 * t2;
    result__[ 51  ] = t15 * t29 * t32 * t336 * t27 * t2 - t280 * t336 * t40 - t81 * t54 * t337 + t343;
    result__[ 52  ] = -t81 * t9 * t15 * t336 + t38 * t336 * t2 + t42 * t343;
    result__[ 53  ] = result__[47];
    result__[ 54  ] = -t280 * t337;
    result__[ 55  ] = t81 * t7 * t336;
    result__[ 56  ] = -1;
    result__[ 57  ] = -1;
    result__[ 58  ] = 1;
    result__[ 59  ] = 1;
    result__[ 60  ] = 1;
    if ( m_debug )
      Mechatronix::check( result__, "steady_state_DequationsDz_sparse", 61 );
  }

  //
  // --------------------------------------------------------------------------
  //
  void
  Bicycle::steady_state_DequationsDz_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 11  ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 2   ;
    iIndex[16] = 2   ; jIndex[16] = 3   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 5   ;
    iIndex[19] = 2   ; jIndex[19] = 6   ;
    iIndex[20] = 2   ; jIndex[20] = 7   ;
    iIndex[21] = 2   ; jIndex[21] = 8   ;
    iIndex[22] = 2   ; jIndex[22] = 10  ;
    iIndex[23] = 2   ; jIndex[23] = 11  ;
    iIndex[24] = 3   ; jIndex[24] = 0   ;
    iIndex[25] = 3   ; jIndex[25] = 2   ;
    iIndex[26] = 3   ; jIndex[26] = 3   ;
    iIndex[27] = 3   ; jIndex[27] = 4   ;
    iIndex[28] = 3   ; jIndex[28] = 5   ;
    iIndex[29] = 3   ; jIndex[29] = 6   ;
    iIndex[30] = 3   ; jIndex[30] = 8   ;
    iIndex[31] = 3   ; jIndex[31] = 10  ;
    iIndex[32] = 3   ; jIndex[32] = 11  ;
    iIndex[33] = 4   ; jIndex[33] = 0   ;
    iIndex[34] = 4   ; jIndex[34] = 2   ;
    iIndex[35] = 4   ; jIndex[35] = 3   ;
    iIndex[36] = 4   ; jIndex[36] = 4   ;
    iIndex[37] = 4   ; jIndex[37] = 6   ;
    iIndex[38] = 4   ; jIndex[38] = 7   ;
    iIndex[39] = 4   ; jIndex[39] = 8   ;
    iIndex[40] = 4   ; jIndex[40] = 9   ;
    iIndex[41] = 4   ; jIndex[41] = 10  ;
    iIndex[42] = 4   ; jIndex[42] = 11  ;
    iIndex[43] = 5   ; jIndex[43] = 0   ;
    iIndex[44] = 5   ; jIndex[44] = 1   ;
    iIndex[45] = 5   ; jIndex[45] = 2   ;
    iIndex[46] = 5   ; jIndex[46] = 3   ;
    iIndex[47] = 5   ; jIndex[47] = 5   ;
    iIndex[48] = 6   ; jIndex[48] = 0   ;
    iIndex[49] = 6   ; jIndex[49] = 1   ;
    iIndex[50] = 6   ; jIndex[50] = 2   ;
    iIndex[51] = 6   ; jIndex[51] = 3   ;
    iIndex[52] = 6   ; jIndex[52] = 4   ;
    iIndex[53] = 6   ; jIndex[53] = 6   ;
    iIndex[54] = 6   ; jIndex[54] = 7   ;
    iIndex[55] = 6   ; jIndex[55] = 8   ;
    iIndex[56] = 7   ; jIndex[56] = 7   ;
    iIndex[57] = 8   ; jIndex[57] = 8   ;
    iIndex[58] = 9   ; jIndex[58] = 0   ;
    iIndex[59] = 10  ; jIndex[59] = 2   ;
    iIndex[60] = 11  ; jIndex[60] = 11  ;
  }

  //   ___        _     ___                       _
  //  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
  //  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
  //  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
  //                                                    |___/
  integer
  Bicycle::postProcessing_numEqns() const
  { return 0; }

  void
  Bicycle::postProcessing(
    real_type       zeta__,
    real_type const X__[],
    real_type const U__[],
    real_type       result__[]
  ) const {

    if ( m_debug )
      Mechatronix::check( result__, "post_processing", 0 );
  }

}

// EOF: Bicycle_Methods.cc
