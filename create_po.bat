xgettext -d digdic -k_ *.cpp -o digdic.po --from-code Shift_JIS
msgmerge ja.po digdic.po -o ja.po
