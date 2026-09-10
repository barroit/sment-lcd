// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

void ipc_start_server(handler_fn handler) {
	xpc_connection_t listener = xpc_connection_create_mach_service("com.example.daemon", NULL, XPC_CONNECTION_MACH_SERVICE_LISTENER);

	xpc_connection_set_event_handler(listener, ^(xpc_object_t peer) {
		if (xpc_get_type(peer) != XPC_TYPE_CONNECTION) return;

		xpc_connection_set_event_handler(peer, ^(xpc_object_t event) {
			if (xpc_get_type(event) != XPC_TYPE_DICTIONARY) return;

			struct ctl_request req;
			req.action = (char*)xpc_dictionary_get_string(event, "action");
			req.payload = (char*)xpc_dictionary_get_string(event, "payload");

			struct ctl_response res;
			handler(&req, &res);

			xpc_object_t reply = xpc_dictionary_create_reply(event);
			xpc_dictionary_set_int64(reply, "status_code", res.status_code);
			xpc_dictionary_set_string(reply, "message", res.message);

			xpc_connection_send_message(peer, reply);
		});
		xpc_connection_resume(peer);
	});

	xpc_connection_resume(listener);
	dispatch_main();
}
