install:
ifdef GW_LOCATION
	@mkdir -p $(GW_LOCATION)/libexec/ruby
	@cp gw_tm_mad_ssh.rb $(GW_LOCATION)/libexec/ruby
	@cp gw_tm_mad_ssh.sh $(GW_LOCATION)/bin/gw_tm_mad_ssh
	@chmod a+x $(GW_LOCATION)/bin/gw_tm_mad_ssh
	@echo SSH TM MAD successfully installed
else
	@echo "  You must define the GW_LOCATION env variable"
	@exit 2
endif
