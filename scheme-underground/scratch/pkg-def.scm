(define-package "scratch"
  (0 1)
  ((install-lib-version (1 3 0)))
  (write-to-load-script
   `((config)
     (load ,(absolute-file-name "packages.scm"
                                (get-directory 'scheme #f)))))
  (install-file "README" 'doc)
  (install-file "NEWS" 'doc)
  (install-string (COPYING) "COPYING" 'doc)
  (install-string "load.scm" 'scheme)
  (install-file "scratch.scm" 'scheme))
