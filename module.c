#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho_pre_routing;
static struct net net;

unsigned int pre_routing_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
  return NF_DROP;
}


static int mod_start(void) {
	printk(KERN_INFO "Module loaded\n");
	nfho_pre_routing.hook = (nf_hookfn*)pre_routing_hook_func;
	nfho_pre_routing.hooknum = NF_INET_PRE_ROUTING;
	nfho_pre_routing.pf = PF_INET;
	nfho_pre_routing.priority = NF_IP_PRI_FIRST;
	nf_register_net_hook(&net, &nfho_pre_routing);
	return 0;
}

static void mod_exit(void) {
	nf_unregister_net_hook(&net, &nfho_pre_routing);
}

module_init(mod_start);
module_exit(mod_exit);
