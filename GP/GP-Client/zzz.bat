if exist *.user (copy *.user *.tmp /Y)
%ACE_ROOT%/bin/mwc.pl -type vc11 -name_modifier "*_vc11" -features boost=1
if exist *.tmp (copy *.tmp *.user /Y)
if exist *.tmp (del *.tmp)
