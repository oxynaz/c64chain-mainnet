file(REMOVE_RECURSE
  "libblockchain_db.a"
  "libblockchain_db.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/blockchain_db.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
