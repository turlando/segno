((c-mode . ((indent-tabs-mode . nil)
            (tab-width . 4)))
 (nil . ((c-file-style . "k&r")
         (flycheck-clang-language-standard . "c99")
         (flychck-clang-include-path ("src"
                                      "include"))
         (whitespace-style . (face
                              tabs tab-mark indentation::tab
                              spaces space-mark indentation::space
                              newline newline-mark
                              trailing)))))
