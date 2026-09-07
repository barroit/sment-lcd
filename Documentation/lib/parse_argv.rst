parse_argv
==========

``parse_argv`` parses command line arguments in-place.

Parser consumes known options and flags. When command entries exist, parser may
also select one command. Arguments left for caller are stored back into same
``argv`` array and terminated with NULL.

Caller owns all value storage. Initialize flag, count, number, string, pick,
and command mode targets before calling ``pa_parse_args()``. Parser updates
target objects, but doesn't initialize them.

Terms
-----

``option``
	Argument that starts with ``--``.

	Examples::

		--name
		--name=value
		--no-name

``flag``
	Argument part introduced by ``-``.

	Examples::

		-x
		-abc
		-xvalue

	In ``-abc``, ``a``, ``b``, and ``c`` are flags. Parser handles them one
	by one unless one flag takes value. A value-taking flag consumes rest of
	string as value.

``bare argument``
	Argument that doesn't start with ``-``.

	Examples::

		file
		add
		origin/main

Basic model
-----------

Parser walks ``argv[1..]`` from left to right.

``argv[0]`` must be set to command name for current parse round. Parser
appends it to diagnostic path.

Example diagnostic path after nested parsing::

	prog add

Known options and flags are applied immediately. Bare arguments are stored in
output ``argv``, rejected, or used for command lookup depending on parser
state.

``pa_parse_args()`` reuses ``argv`` for output. It returns number of arguments
left for caller. Output arguments start at ``argv[0]``.

Parser flags
------------

``PA_STOP_BARE``
	Stop parsing when first bare argument is seen.

	Do not use this with command entries.

``PA_LAX_CMD``
	Make command optional.

	With this flag set, caller must set default command before parsing by
	setting ``*cmd_val`` to the target ``cmd_fn``. If no command is selected,
	parser inserts default command at ``argv[0]``.

	This flag also enables ``PA_STOP_UNKNOWN`` so default command can parse
	its own options and flags later.

	Unknown bare argument closes command lookup. Parser still parses later
	options and flags. Later bare arguments are returned as operands.

	Example, with ``add`` as valid command and ``status`` as default
	command::

		prog add -x
			=> command add selected
			=> argv: add -x

		prog file add -x
			=> command lookup closed at file
			=> argv: status file add -x

		prog file --verbose add
			=> command lookup closed at file
			=> --verbose parsed
			=> argv: status file add

``PA_NO_BARE``
	Reject bare arguments.

``PA_STOP_UNKNOWN``
	Stop parsing when unknown option or unknown flag is seen.

	Bare ``-`` is an unknown flag. With ``PA_STOP_UNKNOWN``, it is stored in
	output ``argv``.

	For unknown flag inside a flag cluster, parser reformats remaining part
	as a flag argument and stores it in output ``argv``. If ``-a`` is known
	and ``-b`` is unknown, ``-ab`` applies ``-a`` and stores ``-b`` in output
	``argv``.

Entry helpers
-------------

``PA_OPT_END()``
	Terminate ``pa_opt`` array. Required for every ``pa_opt`` list.

``PA_OPT_CMD(name, cmd_val, cmd_fn, help)``
	Add command entry.

``PA_OPT_FLAG(name, alias, val, mask, help)``
	Add flag-mask entry.

	Target is ``uint64_t``. Set form ORs ``mask`` into target. Unset form
	clears ``mask`` from target.

``PA_OPT_COUNT(name, alias, val, help)``
	Add counter entry.

	Target is ``int``. Set form increments target. Unset form resets target
	to zero.

``PA_OPT_NUMBER(name, alias, val, help)``
	Add number entry.

	Default target is ``unsigned int``. Use ``PA_OPT_SIGNED`` for
	``int`` target. Use ``PA_OPT_LLONG`` for ``unsigned long long`` target.
	Use both ``PA_OPT_SIGNED`` and ``PA_OPT_LLONG`` for ``long long`` target.

``PA_OPT_STRING(name, alias, val, help)``
	Add string entry.

	Target is ``const char *``. Set form sets target to value. Unset form
	sets target to NULL.

``PA_OPT_FILE(name, alias, val, help)``
	Add string entry with value hint set to ``path``.

``PA_OPT_CMDMODE(name, alias, val, mode, help)``
	Add command mode entry.

	Target is ``int``. Parser sets target to ``mode``. Command mode entries
	for same target (same pointer) are mutually exclusive.

``PA_OPT_PICK(name, alias, val, options, help)``
	Add pick entry.

	Target is ``const char *``. ``options`` is a NULL-terminated string array
	used for validation. Value must match one item in that array.

	With ``PA_OPT_LAX_ARG``, missing value makes parser set target to first
	item in array.

Entry matching
--------------

An entry may provide option form, flag form, or both. NULL ``name`` means no
option form. Zero ``alias`` means no flag form.

Option names may be abbreviated. Parser accepts abbreviation if it identifies
one option. If multiple options match, parser reports ambiguity.

``=`` belongs to option syntax. Text before ``=`` is used for matching. Text
after ``=`` is value.

Negative options
----------------

Unless ``PA_OPT_NO_NEG`` is set, options accept ``--no-name``.

For normal option names, ``--no-name`` sets unset state.

For option names already starting with ``no-``, unset state is inverted.

Caution: unset state doesn't restore target objects to caller's default
value. It applies unset operation defined by entry helper.

``--no-`` is a valid prefix for negatable options. It may be ambiguous when
more than one negatable option exists.

Values
------

An option or flag takes value unless it has ``PA_OPT_NO_ARG``.

Options accept both forms::

	--name=value
	--name value

Flags accept both forms::

	-nvalue
	-n value

For flag clusters, value-taking flag consumes rest of string as value. If
``-o`` takes value, ``-ofile`` assigns ``file`` to ``-o``.

``PA_OPT_LAX_ARG`` makes value optional.

Optional values are greedy. If next argv item exists, parser consumes it as
value. Otherwise parser uses entry default.

Examples::

	--mode --verbose
		=> mode value is "--verbose"

	-m -v
		=> m value is "-v"

Commands
--------

Command is a special bare argument.

When command entries exist, parser tries to match eligible bare argument as
command name. Command name remains in output ``argv`` so next parse round can
use it as ``argv[0]``.

If command entries exist and ``PA_LAX_CMD`` is not set, parser panics on
missing command.

End of options
--------------

``--`` stops option and flag parsing.

Remaining arguments after ``--`` are stored in output ``argv``.

Help
----

``-h`` and ``--help`` print usage and exit.

Usage lines and entries are printed. Entries show command form, flag form,
option form, value hint, and help text. Long text is wrapped.

Return value
------------

``pa_parse_args()`` returns number of arguments stored in output ``argv``.

Parser writes output arguments to ``argv[0..ret - 1]`` and terminates them
with ``NULL``.
