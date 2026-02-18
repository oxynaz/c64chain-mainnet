file(REMOVE_RECURSE
  "libringct.a"
  "libringct.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/ringct.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
