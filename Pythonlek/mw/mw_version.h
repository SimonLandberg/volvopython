/* Copyright (C) 2020 - AB Volvo
 *
 * Define version identifiers needed by application.
 *
 * @file mw_version.h
 *
 */
#ifndef VERSION_H
#define VERSION_H

/*[[[cog
  # Setup codegen of this file
  from avcmpy.codegen import version
]]]*/
//[[[end]]]

/*! PRODUCT shall be set to vcm1 for legacy reasons */
#define PRODUCT vcm1

/*! REVISION is the git version of the complete application repo,
 * which includes application and avcm development kit (mw, platform, tools).
 *
 */
/*[[[cog
  # Generate revision define
  version.cog_revision()
]]]*/
/* <-------------- Generated Code Start (Do not edit!) --------------> */
#define REVISION b565d9a-dirty
#define DATE_TIME "-"__DATE__"-"__TIME__
/* <-------------- Generated Code Stop (Do not edit!) --------------> */
//[[[end]]]

/*! PF_REVISION is set manually to the avcm-vX.Y.Z tag of the platform git repo, that has been integrated in the
 * avcm development kit.
 *
 * Use git log --oneline in the platform repo to find this information.
 *
 */
#define PF_REVISION avcm-v1.0.3

#endif /* VERSION_H */
