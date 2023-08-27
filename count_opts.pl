#!/usr/bin/perl -w

use strict;

my @files = glob "testing/*.out";

my %count;

foreach my $f (@files) {
    print "$f\n";
    open my $INF, "<$f" or die;
    while (my $line = <$INF>) {
        if ($line =~ /^OptID ([0-9]+) matched ([0-9]+) time/) {
            $count{$1} += $2;
        }
    }
    close $INF;
}

foreach my $opt (sort keys %count) {
    print "opt $opt has count $count{$opt}\n";
}
