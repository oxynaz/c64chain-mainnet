file(REMOVE_RECURSE
  "libepee.a"
  "libepee.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/epee.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
