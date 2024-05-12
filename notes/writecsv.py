# Creating a Python script file with the provided Docker data and code to write to an Excel file

import pandas as pd

# Data for Docker images
data = {
    'REPOSITORY': [
        'hcy-multi-write-node146', 'zzy/mysql_sep_state', 'cloud_rucbase_ubuntu',
        'cloud_rucbase_ubuntu', 'block-chain', '<none>', '<none>', '<none>', '<none>',
        'xhc_ubuntu', '<none>', 'pilotscope', '<none>', 'pilotscope-ysm', '<none>',
        '<none>', '<none>', '<none>', 'xys_state_sep', 'cloud-rucbase-dev',
        'mysql_state_sep', 'postgres', 'cwh_mysql_sep', '<none>', 'cwh_mysql_sep',
        'sxy2001/mysql_state_sep', '<none>', '<none>', 'mysql_state_sep', 'ubuntu',
        'hououou/aeong', 'hououou/aeong', 'duoyw/pilotscope', 'workflow-peer',
        '<none>', 'diffkv', 'diffkv', '<none>', 'ubuntu', 'djb2023/rucbase_lab',
        'python', 'ubuntu', 'lrfr5', '<none>', '<none>', '<none>', '<none>', 'lrfr4',
        'lrfr3', 'lrfr2', '<none>', '<none>', '<none>', '<none>', 'lrfr', 'busybox',
        'zqs_redis/ubuntu', 'cg/db', 'ubuntu', 'zqs/postgres', 'opengauss/opengauss',
        '<none>', '<none>', 'polardb/polardb_pg_devel', 'workflow-ca', 'xfyue1998/flink',
        'bitnami/metrics-server', 'postgres', 'registry.cn-beijing.aliyuncs.com/citybrain-app/devtool_centos',
        'registry.cn-beijing.aliyuncs.com/citybrain-app/devtool_javascript_deploy', 'calico/cni',
        'calico/pod2daemon-flexvol', 'calico/node', 'pingcap/tidb-operator', 'mysql',
        'quay.io/prometheus-operator/prometheus-config-reloader', 'quay.io/prometheus/node-exporter',
        'lishizhen/postgresql84_debug', 'flink', 'centos', 'centos', 'quay.io/prometheus/alertmanager',
        'quay.io/brancz/kube-rbac-proxy', 'registry.cn-beijing.aliyuncs.com/citybrain-app/sidecar',
        'cockroachdb/builder', 'registry.aliyuncs.com/google_containers/kube-proxy', 'flink'
    ],
    'TAG': ['latest'] * 60,  # Simplified, real data needed
    'IMAGE ID': [''] * 60,  # Simplified, real data needed
    'CREATED': [''] * 60,  # Simplified, real data needed
    'SIZE': [''] * 60,  # Simplified, real data needed
    'SHARED SIZE': [''] * 60,  # Simplified, real data needed
    'UNIQUE SIZE': [''] * 60,  # Simplified, real data needed
    'CONTAINERS': [0] * 60  # Simplified, real data needed
}

# Create DataFrame
df = pd.DataFrame(data)

# Write to Excel
df.to_excel('docker_data.xlsx', index=False)

print("Data has been written to 'docker_data.xlsx'.")
