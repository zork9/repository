(define-package "tmail"
  (0 1)
  ((install-lib-version (1 3 0)))
  (write-to-load-script
   `((config)
     (load ,(absolute-file-name "packages.scm"
                                (get-directory 'scheme #f)))))
  (install-file "README" 'doc)
  (install-file "NEWS" 'doc)
  (install-string (COPYING) "COPYING" 'doc)
  (install-file "packages.scm" 'scheme)
  (install-file "tdaemon.scm" 'scheme)
  (install-file "tforks.scm" 'scheme)
  (install-file "tclient.scm" 'scheme)
  (install-file "trecords.scm" 'scheme)
  (install-file "tmailbox.scm" 'scheme)
  (install-file "tmailbox-load.scm" 'scheme)
  (install-file "util.scm" 'scheme)
  (install-file "tserver.scm" 'scheme))
