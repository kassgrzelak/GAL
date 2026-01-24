# Open<ins>G</ins>L <ins>A</ins>bstraction <ins>L</ins>ayer (GAL)

Lorem ipsum descriptionus not writteth.

## Optional Macros

These are macros you can define before including GAL in your project to alter its behavior.

`GAL_ERROR_LOGGING`: Allow GAL to log runtime errors to cerr, even if the exception is caught.\
`GAL_WARNING_LOGGING`: Allow GAL to log warnings for non-fatal errors to cerr (don't know what this will be used for
yet).\
`GAL_INFO_LOGGING`: Allow GAL to log verbose info about everything it's doing to cout for debugging purposes.\
`GAL_VERBOSE`: Defines all the above logging macros.

`GAL_DONT_INCLUDE_GLAD`: By default, GAL links to the vendored glad v2 library, which is configured for OpenGL 4.6 core
profile. To provide your own glad v2, define this macro and make sure to pass in the OpenGL version you'd like to use
(if it's different) to gal::init().\
`GAL_DONT_INCLUDE_GLFW`: By default, GAL links to GLFW 3.4. If you'd like to use your own version of GLFW (provided it
doesn't break compatibility with 3.4), define this macro.