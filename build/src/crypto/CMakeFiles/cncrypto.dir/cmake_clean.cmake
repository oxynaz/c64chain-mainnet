file(REMOVE_RECURSE
  "libcncrypto.a"
  "libcncrypto.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/cncrypto.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
