## viper
viper can parse yaml files to a struct, the struct should satisfy following patterns 
1. member of struct MUST be public.
2. member's name must be the same in yaml file. (1. have the more priority.)
3. the `yaml:"xx"` maybe be not effective.
