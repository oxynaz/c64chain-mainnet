file(REMOVE_RECURSE
  "libmultisig.a"
  "libmultisig.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/multisig.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
