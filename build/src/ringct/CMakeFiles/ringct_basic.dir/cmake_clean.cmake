file(REMOVE_RECURSE
  "libringct_basic.a"
  "libringct_basic.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/ringct_basic.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
