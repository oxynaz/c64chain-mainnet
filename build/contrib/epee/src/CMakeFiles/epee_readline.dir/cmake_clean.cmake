file(REMOVE_RECURSE
  "libepee_readline.a"
  "libepee_readline.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/epee_readline.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
