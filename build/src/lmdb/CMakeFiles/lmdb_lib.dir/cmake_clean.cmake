file(REMOVE_RECURSE
  "liblmdb_lib.a"
  "liblmdb_lib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/lmdb_lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
