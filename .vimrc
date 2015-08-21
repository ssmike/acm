set backspace=indent,eol,start
set nocompatible
"language messages en
set tabstop=4
set shiftwidth=4
set smarttab
set expandtab
set autoread
set cindent
set number
set expandtab
imap {<CR>  {<CR>}<LEFT><CR><UP><SPACE><SPACE><SPACE><SPACE>
nmap <TAB> :tabn<CR>
nmap <BACKSPACE> :tabp<CR>
nmap <F2> :tabnew<CR>
nmap <F3> :q!<CR>
imap <F1> <ESC>:w<CR>a
nmap <F1> :w<CR>
set makeprg=g++\ -O2\ -Wall\ -Wextra\ -Wno-unused-result\ -Wno-unused-parameter\ -std=c++11\ -DLOCAL\ %\ -o\ %<
au BufNewFile *.cpp 0r /home/moon/template.cpp | 30 | set syntax=cpp
nmap <F9> :make<CR>
imap <F9> <ESC>:make<CR>a
nmap <F8> :!./%<<CR>
imap <F5> <ESC>:!./%<<CR>a
nmap <F5> :!./%<<CR>
nmap s :w<CR>
syn on
set guioptions-=T
colorscheme koehler
set guifont=Source_Code_Pro:h10
set guioptions-=m
set guioptions-=e
vmap . "+
nmap . "+
set mouse=a
autocmd BufEnter * lcd %:p:h
set nobackup
