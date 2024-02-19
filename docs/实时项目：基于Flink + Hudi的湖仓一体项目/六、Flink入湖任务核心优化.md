## 基于 RateLimiter 的线程级限速开发
### 问：Flink 的 Task 是进程的还是线程的？
一些基本的概念：
- **Task**

物理图的节点（StreamGraph/JobGraph/ExecutionGraph）。任务是工作的基本单元，由 Flink 的运行时执行。任务精确地封装运算符或运算符链的一个并行实例。Task 是逻辑概念，一个 Operator 就代表一个 Task（多个Opertator 被 chain 之后产生的新 Operator 算一个 Operator）就是 Flink 作业计算时的算子，比如 map、keyBy 等等。

- **Sub Task**


### RateLimiter 代码
```java
package com.xx.udfs.udf;

import com.google.common.util.concurrent.RateLimiter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import org.apache.commons.lang.StringUtils;
import org.apache.flink.table.functions.FunctionContext;
import org.apache.flink.table.functions.ScalarFunction;

public class FlinkRateLimiterUDF extends ScalarFunction {
    private static final Logger log = LoggerFactory.getLogger(FlinkRateLimiterUDF.class);
    private static final Long DEFAULT_VALUE = Long.valueOf(1000L);
    private String rateLimitNum;
    private RateLimiter rateLimiter;

    public void open(FunctionContext context) throws IOException {
        log.info("FlinkRateLimiterUDF init");
        rateLimitNum = context.getJobParameter("rate_limit_num", "1000");
        log.info("FlinkRateLimiterUDF open method finished.");
    }

    public String eval(String what_ever) {
        String rate = rateLimitNum;
        if (StringUtils.isBlank(rate)) {
            return what_ever;
        }
        if (StringUtils.isNotBlank(rate)) {
            Long rateR = Long.valueOf(rate);
            if (this.rateLimiter == null) {
                this.rateLimiter = RateLimiter.create(rateR.longValue());
            } else if (rateR.longValue() != this.rateLimiter.getRate()) {
                this.rateLimiter.setRate(rateR.longValue());
            }
        }
        // 核心代码
        this.rateLimiter.acquire(1);
        return what_ever;
    }
}
```

```SQL
CREATE FUNCTION FlinkRateLimiterUDF AS 'com.xx.flnik.udfs.FlinkRateLimiterUDF';

CREATE VIEW aaa AS
SELECT
    penalize_id,
    app_id,
    ...
    FlinkRateLimiterUDF(biz_date)
FROM source_a;
```

```SQL
CREATE TABLE kafka_source (
    ...
    proc AS PROCTIME()
)
WITH (
    'connector' = 'kafka',
    'properties.bootstrap.servers' = 'hadoop1:9092',
    'properties.group.id' = 'dwd_creator_penalize_ticket',
    'kafka.topic' = 'ods_dwd_creator_penalize_ticket',
    'format' = 'json',
    -- 'scan.startup.mode' = 'latest-offset',
    'scan.startup.mode' = 'timestamp',
    'scan.startup.timestamp-millis' = '160000000000',
    'parallelism' = '5'
    'rate-limit' = '20000'
);

CREATE TABLE doris_sink (
    ...
)
WITH (
    ...
);
```