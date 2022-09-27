-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               10.8.3-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Dumping structure for table model_runs.configuration_statistics
CREATE TABLE IF NOT EXISTS `configuration_statistics` (
  `label` char(128) NOT NULL,
  `strain_1_transmission_probability_aggregated_net_fluctuation` int(11) NOT NULL DEFAULT 0,
  `strain_1_transmission_probability_aggregated_stable_net` int(11) NOT NULL,
  `strain_1_transmission_probability_basic_net_fluctuation` int(11) NOT NULL,
  `strain_1_transmission_probability_basic_stable_net` int(11) NOT NULL,
  `strain_2_transmission_probability_aggregated_net_fluctuation` int(11) NOT NULL,
  `strain_2_transmission_probability_aggregated_stable_net` int(11) NOT NULL,
  `strain_2_transmission_probability_basic_net_fluctuation` int(11) NOT NULL,
  `strain_2_transmission_probability_basic_stable_net` int(11) NOT NULL,
  `aggregated_net_with_fluctuation_number` int(11) NOT NULL,
  `aggregated_net_with_fluctuation_size` int(11) NOT NULL,
  `aggregated_stable_net_size` int(11) NOT NULL,
  `basic_net_with_fluctuation_fluctuation` int(11) NOT NULL,
  `basic_net_with_fluctuation_number` int(11) NOT NULL,
  `basic_net_with_fluctuation_size` int(11) NOT NULL,
  `basic_stable_net_size` int(11) NOT NULL,
  `population_size` int(11) NOT NULL,
  `strain1_random_transmission_probability` int(11) NOT NULL,
  `strain2_random_transmission_probability` int(11) NOT NULL,
  `shuffle_stable_nets` int(11) NOT NULL,
  `strain_1_contagiousness_begin` int(11) NOT NULL DEFAULT 0,
  `strain_1_contagiousness_end` int(11) NOT NULL DEFAULT 0,
  `strain_2_contagiousness_begin` int(11) NOT NULL DEFAULT 0,
  `strain_2_contagiousness_end` int(11) NOT NULL DEFAULT 0,
  `immunity_reduction_time` int(11) NOT NULL DEFAULT 0,
  `immunity_reduction_weight` int(11) NOT NULL DEFAULT 0,
  `initial_strain1cases` char(128) NOT NULL DEFAULT '0',
  `initial_strain2cases` char(128) NOT NULL DEFAULT '0',
  `first_strain2_appearance` int(11) NOT NULL DEFAULT 0,
  `number_of_runs` int(11) DEFAULT NULL,
  `max_max_new` int(11) DEFAULT NULL,
  `min_max_new` int(11) DEFAULT NULL,
  `mean_max_new` float DEFAULT NULL,
  `standard_deviation_max_new` float DEFAULT NULL,
  `max_max1_new` int(11) DEFAULT NULL,
  `min_max1_new` int(11) DEFAULT NULL,
  `mean_max1_new` float DEFAULT NULL,
  `standard_deviation_max1_new` float DEFAULT NULL,
  `max_max2_new` int(11) DEFAULT NULL,
  `min_max2_new` int(11) DEFAULT NULL,
  `mean_max2_new` float DEFAULT NULL,
  `standard_deviation_max2_new` float DEFAULT NULL,
  `max_max_post1` int(11) DEFAULT NULL,
  `min_max_post1` int(11) DEFAULT NULL,
  `mean_max_post1` float DEFAULT NULL,
  `standard_deviation_max_post1` float DEFAULT NULL,
  `max_post1_at_end` int(11) DEFAULT NULL,
  `min_post1_at_end` int(11) DEFAULT NULL,
  `mean_post1_at_end` float DEFAULT NULL,
  `standard_deviation_post1_at_end` float DEFAULT NULL,
  `max_post2_at_end` int(11) DEFAULT NULL,
  `min_post2_at_end` int(11) DEFAULT NULL,
  `mean_post2_at_end` float DEFAULT NULL,
  `standard_deviation_post2_at_end` float DEFAULT NULL,
  `max_length` int(11) DEFAULT NULL,
  `min_length` int(11) DEFAULT NULL,
  `mean_length` float DEFAULT NULL,
  `standard_deviation_length` float DEFAULT NULL,
  `max_time_to_complete_replacement` int(11) DEFAULT NULL,
  `min_time_to_complete_replacement` int(11) DEFAULT NULL,
  `mean_time_to_complete_replacement` float DEFAULT NULL,
  `standard_deviation_time_to_complete_replacement` float DEFAULT NULL,
  `max_time_to_dominance` int(11) DEFAULT NULL,
  `min_time_to_dominance` int(11) DEFAULT NULL,
  `mean_time_to_dominance` float DEFAULT NULL,
  `standard_deviation_time_to_dominance` float DEFAULT NULL,
  `max_immunity_at_peak` float DEFAULT NULL,
  `min_immunity_at_peak` float DEFAULT NULL,
  `mean_immunity_at_peak` float DEFAULT NULL,
  `standard_deviation_immunity_at_peak` float DEFAULT NULL,
  `max_immunity_at_end` float DEFAULT NULL,
  `min_immunity_at_end` float DEFAULT NULL,
  `mean_immunity_at_end` float DEFAULT NULL,
  `standard_deviation_immunity_at_end` float DEFAULT NULL,
  `max_immunity_at_complete_replacement` float DEFAULT NULL,
  `min_immunity_at_complete_replacement` float DEFAULT NULL,
  `mean_immunity_at_complete_replacement` float DEFAULT NULL,
  `standard_deviation_immunity_at_complete_replacement` float DEFAULT NULL,
  `max_immunity_at_last_90pcnt_max` float DEFAULT NULL,
  `min_immunity_at_last_90pcnt_max` float DEFAULT NULL,
  `mean_immunity_at_last_90pcnt_max` float DEFAULT NULL,
  `max_immunity_at_last_75pcnt_max` float DEFAULT NULL,
  `min_immunity_at_last_75pcnt_max` float DEFAULT NULL,
  `mean_immunity_at_last_75pcnt_max` float DEFAULT NULL,
  `standard_deviation_immunity_at_last_75pcnt_max` float DEFAULT NULL,
  `standard_deviation_immunity_at_last_90pcnt_max` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='parameters and statistics of a model run group';

-- Data exporting was unselected.

-- Dumping structure for table model_runs.header
CREATE TABLE IF NOT EXISTS `header` (
  `model_run_key` char(128) NOT NULL,
  `label` char(128) NOT NULL,
  `strain_1_transmission_probability_aggregated_net_fluctuation` int(11) NOT NULL DEFAULT 0,
  `strain_1_transmission_probability_aggregated_stable_net` int(11) NOT NULL,
  `strain_1_transmission_probability_basic_net_fluctuation` int(11) NOT NULL,
  `strain_1_transmission_probability_basic_stable_net` int(11) NOT NULL,
  `strain_2_transmission_probability_aggregated_net_fluctuation` int(11) NOT NULL,
  `strain_2_transmission_probability_aggregated_stable_net` int(11) NOT NULL,
  `strain_2_transmission_probability_basic_net_fluctuation` int(11) NOT NULL,
  `strain_2_transmission_probability_basic_stable_net` int(11) NOT NULL,
  `aggregated_net_with_fluctuation_number` int(11) NOT NULL,
  `aggregated_net_with_fluctuation_size` int(11) NOT NULL,
  `aggregated_stable_net_size` int(11) NOT NULL,
  `aggregated_stable_net_number` int(11) NOT NULL DEFAULT 0,
  `basic_net_with_fluctuation_fluctuation` int(11) NOT NULL,
  `basic_net_with_fluctuation_number` int(11) NOT NULL,
  `basic_net_with_fluctuation_size` int(11) NOT NULL,
  `basic_stable_net_size` int(11) NOT NULL,
  `population_size` int(11) NOT NULL,
  `strain1_random_transmission_probability` int(11) NOT NULL,
  `strain2_random_transmission_probability` int(11) NOT NULL,
  `shuffle_stable_nets` int(11) NOT NULL,
  `strain_1_contagiousness_begin` int(11) NOT NULL DEFAULT 0,
  `strain_1_contagiousness_end` int(11) NOT NULL DEFAULT 0,
  `strain_2_contagiousness_begin` int(11) NOT NULL DEFAULT 0,
  `strain_2_contagiousness_end` int(11) NOT NULL DEFAULT 0,
  `immunity_reduction_time` int(11) NOT NULL DEFAULT 0,
  `immunity_reduction_weight` int(11) NOT NULL DEFAULT 0,
  `initial_strain1cases` char(128) NOT NULL DEFAULT '0',
  `initial_strain2cases` char(128) NOT NULL DEFAULT '0',
  `first_strain2_appearance` int(11) NOT NULL DEFAULT 0,
  `environmental_constraints_change_time` int(11) NOT NULL DEFAULT 0,
  `environmental_constraints_change_weight` int(11) NOT NULL DEFAULT 0,
  `max` int(11) DEFAULT 0,
  `max_1` int(11) DEFAULT 0,
  `max_2` int(11) DEFAULT 0,
  `max_post_1` int(11) DEFAULT 0,
  `post_1` int(11) DEFAULT 0,
  `post_2` int(11) DEFAULT 0,
  `initial` int(11) DEFAULT 0,
  `length` int(11) DEFAULT 0,
  `time_to_dominance` int(11) DEFAULT 0,
  `first_close_max` int(11) DEFAULT 0,
  `last_close_max` int(11) DEFAULT 0,
  `time_to_complete_replacement` int(11) DEFAULT 0,
  `immunity_at_complete_replacement` float DEFAULT NULL,
  `immunity_at_peak` float DEFAULT NULL,
  `immunity_at_last_90pcnt_max` float DEFAULT NULL,
  `immunity_at_last_75pcnt_max` float DEFAULT NULL,
  `immunity_at_end` float DEFAULT NULL,
  PRIMARY KEY (`model_run_key`,`label`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='the parameters of a model run';

-- Data exporting was unselected.

-- Dumping structure for table model_runs.population_state
CREATE TABLE IF NOT EXISTS `population_state` (
  `model_run_key` char(128) NOT NULL,
  `generation` int(11) NOT NULL DEFAULT 0,
  `new_activity` int(11) NOT NULL DEFAULT 0,
  `new_strain1_activity` int(11) NOT NULL DEFAULT 0,
  `new_strain2_activity` int(11) NOT NULL DEFAULT 0,
  `initial_state` int(11) NOT NULL DEFAULT 0,
  `strain1_activity` int(11) NOT NULL DEFAULT 0,
  `strain2_activity` int(11) NOT NULL DEFAULT 0,
  `post_strain1_activity` int(11) NOT NULL DEFAULT 0,
  `post_strain2_activity` int(11) NOT NULL DEFAULT 0,
  `nets_with_fluctuation_and_strain1_activity` int(11) NOT NULL DEFAULT 0,
  `nets_with_fluctuation_and_strain2_activity` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`model_run_key`,`generation`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Data exporting was unselected.

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
