import synodic.portability;

static_assert(port::HasAssertions || !port::HasAssertions);

int main()
{
	return 0;
}
