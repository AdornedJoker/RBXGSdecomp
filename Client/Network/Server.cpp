#include "Server.h"
#include "util/standardout.h"
#include "util/Debug.h"

namespace RBX
{
	namespace Network
	{
		void Server::start(int port, int threadSleepTime)
		{
			SocketDescriptor socketDescriptor(port, "");
			if (!this->rakPeer.get()->Startup(32, threadSleepTime, &socketDescriptor, 1))
				throw std::runtime_error("Failed to start network server");

			this->outgoingPort = port;

			StandardOut::singleton()->print(MESSAGE_INFO, "Starting network server on port %d", port);
			StandardOut::singleton()->print(MESSAGE_INFO, "IP addresses:");

			for(unsigned int i = 0; i < this->rakPeer->GetNumberOfAddresses(); i++)
				StandardOut::singleton()->print(MESSAGE_INFO, "%s", this->rakPeer->GetLocalIP(i));

			Peer::updateNetworkSimulator();
		}

		void Server::stop(int blockDuration)
		{
			if(this->rakPeer.get()->IsActive())
				this->rakPeer.get()->Shutdown(blockDuration);

			Instance::removeAllChildren();
		}
	}
}