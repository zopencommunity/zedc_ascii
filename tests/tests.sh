#!/bin/sh

FAILED=0
PASSED=0
TOTAL=0

test_passed() {
	PASSED=$(( PASSED + 1 ))
}

test_failed() {
	FAILED=$(( FAILED + 1 ))
}

test_version()
{
	VERSION=$(./getVersion)
	EXPECTED_VERSION="1.2.11"

	if [ "$VERSION" = "$EXPECTED_VERSION" ]; then
		test_passed
	else
		test_failed
	fi
}

test_compression()
{
	./compress_test
	if [ $? -eq 0 ]; then
		test_passed
	else
		test_failed
	fi
}


#################################################
# RUN TESTS                                       #
#################################################
test_version
test_compression

#################################################
# RESULTS                                       #
#################################################
TOTAL=$(( FAILED + PASSED ))
echo "================================================"
echo "=                 RESULTS                      ="
echo "================================================"
echo "Total tests:  $TOTAL"
echo "Passed:       $PASSED"
echo "Failed:       $FAILED"

if [ $FAILED -gt 0 ]; then
	exit 1
fi
