description('Test setting the hostname attribute of the URL in HTMLAnchorElement.');

var a = document.createElement('a');

debug("Basic test");
a.href = "https://www.mydomain.com:8080/path/";
a.hostname = "www.otherdomain.com";
shouldBe("a.href", "'https://www.otherdomain.com:8080/path/'");

// IE8 throws an exception "The URL is invalid".
try {
debug("Extra slashes before hostname");
a.href = "https://www.mydomain.com:8080/path/";
a.hostname = "//www.otherdomain.com";
shouldBe("a.href", "'https://www.otherdomain.com:8080/path/'");
} catch(e) {
debug("Exception: " + e.description);
}

// Firefox 3.5.2 does not allow setting the host to foo: protocol
debug("Set hostname to URL with foo: protocol");
a.href = "foo://www.mydomain.com/path/";
a.hostname = "www.otherdomain.com";
shouldBe("a.href", "'foo://www.otherdomain.com/path/'");

// IE8 converts null to "null", which is not the right thing to do.
// Firefox 3.5.2 allows setting the hostname to null, which is wrong per
// http://dev.w3.org/html5/spec/infrastructure.html#url-decomposition-idl-attributes .
debug("Set hostname to null");
a.href = "https://www.mydomain.com:8080/path/";
a.hostname = null;
shouldBe("a.href", "'https://www.mydomain.com:8080/path/'");

// Both IE8 and Firefox 3.5.2 allow setting the host to empty string, against the spec at
// http://dev.w3.org/html5/spec/infrastructure.html#url-decomposition-idl-attributes .
// Since both do that in a buggy way, WebKit should not follow either one of them.
debug("Set hostname to empty string");
a.href = "https://www.mydomain.com:8080/path/";
a.hostname = "";
shouldBe("a.href", "'https://www.mydomain.com:8080/path/'");

// IE8 fails to process really: protocol.
debug("Set hostname to URL with 2 colons");
a.href = "really:bad:url";
a.hostname = "mydomain.com";
shouldBe("a.href", "'really:bad:url'");

// The expected behavior should change when the character table is updated.
// IE8 encodes the space in the hostname.
// Firefox3.5.2 and WebKit consider space as illegal character and would not set 
// the new hostname.
debug("Set a hostname that contains space in it");
a.href = "http://www.my domain.com/path/";
a.hostname = "www.other domain.com";
shouldBe("a.href", "'http://www.my domain.com/path/'");

// IE8 throws an exception "The URL is invalid".
try {
debug("Set hostname on a local file");
a.href = "c:/path/testurl.html";
a.hostname= "a";
shouldBe("a.href", "'c:/path/testurl.html'");
} catch(e) {
debug("Exception: " + e.description);
}

debug("Set hostname to undefined");
a.href = "https://www.mydomain.com:8080/path/";
a.hostname = undefined;
shouldBe("a.href", "'https://undefined:8080/path/'");

var successfullyParsed = true;
