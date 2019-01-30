" Add this commented bit to YOUR .vimrc:
" let file_cwd = expand('%:p:h')
" let vimrc_path = fnamemodify(findfile(".vimrc", file_cwd.";"), ':p')
" 
" if !empty(glob(vimrc_path))
"         if fnameescape(vimrc_path) != fnameescape($MYVIMRC)
"                 exec ':source '.fnameescape(vimrc_path)
"         endif
" endif

autocmd BufEnter * silent! lcd %:p:h

function FormatFile()
  let cwd = expand('%:p:h')
  let clang_path = fnamemodify(findfile("clang-format.py", cwd.";"), ':p')
  let l:lines="all"
  execute 'pyf' clang_path
endfunction

autocmd BufWritePre *.h,*.cc,*.cpp call FormatFile()
