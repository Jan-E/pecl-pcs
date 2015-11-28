--TEST--
Retrieve information about virtual files
--EXTENSIONS--
pcs
--INI--
ptest.load_code3=1
--SKIPIF--
<?php if (!extension_loaded("pcs")) print "skip"; ?>
--FILE--
<?php

var_dump(PCS\Mgr::fileCount());

print_r(PCS\Mgr::fileInfos());

?>
===DONE===
--EXPECTF--
Loaded code3 set
int(9)
Array
(
    [0] => Array
        (
            [flags] => 3
            [load] => 3
            [size] => 134
            [path] => internal/parser/ParserInterface.php
        )

    [1] => Array
        (
            [flags] => 3
            [load] => 3
            [size] => 5716
            [path] => internal/parser/StringParser.php
        )

    [2] => Array
        (
            [flags] => 3
            [load] => 3
            [size] => 3135
            [path] => internal/tools/embed.php
        )

    [3] => Array
        (
            [flags] => 0
            [load] => 2
            [size] => 147
            [path] => ext/ptest/constclass.txt
        )

    [4] => Array
        (
            [flags] => 0
            [load] => 3
            [size] => 0
            [path] => ext/ptest/empty.txt
        )

    [5] => Array
        (
            [flags] => 0
            [load] => 2
            [size] => 87
            [path] => ext/ptest/func.txt
        )

    [6] => Array
        (
            [flags] => 0
            [load] => 3
            [size] => 107
            [path] => ext/ptest/nosymbols.txt
        )

    [7] => Array
        (
            [flags] => 0
            [load] => 3
            [size] => 11
            [path] => ext/ptest/test.txt
        )

    [8] => Array
        (
            [flags] => 0
            [load] => 3
            [size] => 253
            [path] => ext/ptest/unregistered.txt
        )

)
===DONE===
