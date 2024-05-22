import "pe"

rule CeosRule
{
    strings:
        $str1 = { 57 69 6e 64 6f 77 73 }
        $str2 = { 31 2e 31 2e 31 2e 31 }
	$base64_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    condition:
        $str1 and $str2 and $base64_string
}

rule ImpHashRule
{
   condition:
	pe.imphash() == "1fe57b147f70a2802789bdb00aa2731e"
}

